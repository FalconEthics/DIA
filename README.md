# E-DIA: Enhanced Duplicate Image Analyzer

E-DIA is a command-line application written in C that helps you efficiently find and delete duplicate images in a directory. It utilizes MD5 hashing to identify duplicate images, ensuring high precision and accuracy. This tool is designed to save you time by automating the process of detecting and removing duplicate images, even if they have different file formats (e.g., PNG or JPG).

## Features

- **High Precision**: E-DIA uses MD5 hashing to accurately identify duplicate images based on their content, ensuring that no unique images are accidentally deleted.

- **Fast Performance**: Written in C, E-DIA is optimized for speed and efficiency, making it a fast solution for managing large image collections.

- **Easy to Use**: E-DIA is a command-line tool with a straightforward interface. Simply provide the directory path, and it will scan for and remove duplicates automatically.

## Getting Started

Follow these steps to use E-DIA:

1. **Compile the Code**: Compile the provided C code using a C compiler. For example, you can use GCC with the following command:

   ```bash
   gcc -o edia edia.c -lcrypto
   ```

   This command will create an executable named `edia`.

2. **Run the Application**: Execute the compiled program:

   ```bash
   ./edia
   ```

3. **Enter the Directory Path**: You will be prompted to enter the path to the directory containing your images. Provide the directory path and press Enter.

4. **Duplicate Detection**: E-DIA will scan the specified directory for duplicate images based on their content. When duplicates are found, they will be automatically deleted, and you will see a confirmation message.

## Caution

- E-DIA will permanently delete duplicate images. Make sure to create a backup of your images or use it on a copy of your data if you have any concerns.

- Ensure that you have proper permissions to delete files in the specified directory.

- The tool currently supports only MD5-based duplicate detection. If you have images with different content but the same MD5 hash (unlikely but possible), use caution.

## License

This project is licensed under the GNU License. See the [LICENSE](./LICENSE) file for details.

## Contributions

Contributions to enhance and expand the functionality of E-DIA are welcome. Please submit issues and pull requests on the project's [GitHub repository](https://github.com/FalconEthics/E-DIA).

## Acknowledgments

E-DIA was created to simplify the process of managing image collections. Special thanks to the open-source community for their contributions and support.

**Disclaimer**: This tool is provided as-is, and the developer is not responsible for any data loss or unintended consequences. Use it responsibly and with caution.