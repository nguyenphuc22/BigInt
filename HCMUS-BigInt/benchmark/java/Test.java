import java.math.BigInteger;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.IOException;
import java.util.List;

public class Test {
    public static void main(String[] args) {
        FileReader fileReader = new FileReader();
        List<String> lines = fileReader.readFile("../../CreateTestCaseBigInt/data/add.txt");

        // In ra nội dung của file
        for (String line : lines) {
            System.out.println(line);
        }
    }
}


public class FileReader {
    public List<String> readFile(String filePath) {
        List<String> lines = null;
        try {
            lines = Files.readAllLines(Paths.get(filePath));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return lines;
    }
}