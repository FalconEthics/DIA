import java.io.File
import java.security.MessageDigest
import javax.xml.bind.DatatypeConverter

fun main() {
    val dirPath = getInputDirectory()
    val dir = File(dirPath)
    if (!dir.exists()) {
        println("Directory does not exist.")
        return
    }
    if (!dir.isDirectory) {
        println("Path is not a directory.")
        return
    }
    val imageFiles = dir.listFiles { file -> file.isFile && file.extension.matches(Regex("(?i)jpe?g|png|gif|bmp")) }
    if (imageFiles.isEmpty()) {
        println("No image files found.")
        return
    }
    val md5Map = HashMap<String, File>()
    for (file in imageFiles) {
        val md5 = getMD5(file)
        if (md5Map.containsKey(md5)) {
            println("Deleting duplicate file ${file.name}")
            file.delete()
        } else {
            md5Map[md5] = file
        }
    }
    println("Duplicate images removed.")
}

fun getInputDirectory(): String {
    println("Enter directory path:")
    return readLine()!!
}

fun getMD5(file: File): String {
    val md = MessageDigest.getInstance("MD5")
    val digest = md.digest(file.readBytes())
    return DatatypeConverter.printHexBinary(digest).toUpperCase()
}