package org.example;
// imports
import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.io.FileInputStream;
import java.security.MessageDigest;
import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.io.FileNotFoundException;

public class Main {
    // Main method
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the directory path:");
        String directoryPath = scanner.nextLine();
        File directory = new File(directoryPath);

        // Check if the directory exists and is not empty
        if (!directory.exists() || !directory.isDirectory() || directory.list().length == 0) {
            System.out.println("The directory is empty or does not exist.");
            return;
        }

        // Check if the user has read and write permissions to the directory
        if (!directory.canRead() || !directory.canWrite()) {
            System.out.println("You don't have read and write permissions for this directory.");
            return;
        }

        // Get a list of all image files in the directory
        List<File> imageFiles = new ArrayList<>();
        for (File file : directory.listFiles()) {
            if (isImageFile(file)) {
                imageFiles.add(file);
            }
        }

        // Check if there are any image files in the directory
        if (imageFiles.isEmpty()) {
            System.out.println("There are no image files in the directory.");
            return;
        }

        // Prompt the user to choose between bulk compress or delete duplicates
        System.out.println("Please choose an option: (1) Bulk compress (2) Delete duplicates");
        int option = scanner.nextInt();
        scanner.nextLine();

        // Execute the chosen task
        if (option == 1) {
            // Prompt the user to enter the compression percentage
            System.out.println("Please enter the compression percentage (0-100):");
            int compressionPercentage = scanner.nextInt();
            scanner.nextLine();
            System.out.println("Compressing images...");
            for (int i = 0; i < imageFiles.size(); i++) {
                File imageFile = imageFiles.get(i);
                // Compress the image
                compressImage(imageFile, compressionPercentage);
                System.out.println("Progress: " + (i + 1) * 100 / imageFiles.size() + "%");
            }
            System.out.println("Compression complete!");
        } else if (option == 2) {
            // Delete duplicate images
            System.out.println("Deleting duplicates...");
            Set<String> hashSet = new HashSet<>();
            for (int i = 0; i < imageFiles.size(); i++) {
                File imageFile = imageFiles.get(i);
                String fileHash = null;
                try {
                    // Get the hash of the image
                    fileHash = getImageHash(imageFile);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                } catch (NoSuchAlgorithmException e) {
                    throw new RuntimeException(e);
                }
                if (hashSet.contains(fileHash)) {
                    // Delete the duplicate image
                    imageFile.delete();
                } else {
                    // Add the hash to the hash set
                    hashSet.add(fileHash);
                }
                System.out.println("Progress: " + (i + 1) * 100 / imageFiles.size() + "%");
            }
            System.out.println("Deletion complete!");
        } else {
            System.out.println("Invalid option selected.");
        }
    }

    private static boolean isImageFile(File file) {
        // Check if the file is an image file
        String fileName = file.getName();
        String extension = fileName.substring(fileName.lastIndexOf(".") + 1).toLowerCase();
        return extension.equals("jpg") || extension.equals("jpeg") || extension.equals("png");
    }

    private static void compressImage(File imageFile, int compressionPercentage) {
        try {
            // Read the image file
            BufferedImage originalImage = ImageIO.read(imageFile);
            if (originalImage == null) {
                // If the image file is invalid, skip it
                System.err.println("Failed to read image file: " + imageFile.getAbsolutePath());
                return;
            }
            int originalWidth = originalImage.getWidth();
            int originalHeight = originalImage.getHeight();
            double compressionRatio = (double) compressionPercentage / 100;
            int newWidth = (int) (originalWidth * compressionRatio);
            int newHeight = (int) (originalHeight * compressionRatio);
            // Create a new image with the new dimensions
            BufferedImage resizedImage = new BufferedImage(newWidth, newHeight, originalImage.getType());
            Graphics2D graphics2D = resizedImage.createGraphics();
            graphics2D.drawImage(originalImage, 0, 0, newWidth, newHeight, null);
            graphics2D.dispose();
            ImageIO.write(resizedImage, "jpg", imageFile);
        } catch (IOException e) {
            System.err.println("Failed to compress image: " + imageFile.getAbsolutePath());
            e.printStackTrace();
        }
    }



    private static String getImageHash(File imageFile) throws IOException, NoSuchAlgorithmException {
        try {
            // Get the hash of the image file
            FileInputStream fileInputStream = new FileInputStream(imageFile);
            MessageDigest messageDigest = MessageDigest.getInstance("MD5");
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
               // Update the message digest
                messageDigest.update(buffer, 0, bytesRead);
            }
            byte[] digest = messageDigest.digest();
            StringBuilder stringBuilder = new StringBuilder();
            for (byte b : digest) {
                stringBuilder.append(String.format("%02x", b));
            }
            // Close the file input stream
            fileInputStream.close();
            return stringBuilder.toString();
        } catch (FileNotFoundException e) {
            // If the image file is not found, throw an exception
            System.err.println("File not found: " + imageFile.getAbsolutePath());
            throw new IOException("Failed to read image file", e);
        }
    }
}

// copyright 2022 ~ Soumik Das