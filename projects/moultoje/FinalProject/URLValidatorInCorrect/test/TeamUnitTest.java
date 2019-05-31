import junit.framework.TestCase;
import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.util.List;

//based off of the original test implementation this class will unit test various urls against the known invalid tester

public class TeamUnitTest extends TestCase {

	//constructor
	public TeamUnitTest(String testName) {
		super(testName);
	}

	//load the data
	@Override
	protected void setUp() {
		File directory = new File("./");
        System.out.println(directory.getAbsolutePath());
        
        
	}

	//test good urls
	public void testGoodUrls()  throws IOException {
		UrlValidator urlVal = new UrlValidator(null, null, 1);
		List<String> goodUrls = Files.readAllLines(new File("goodUrls.txt").toPath(), Charset.defaultCharset());
		for (int i = 0; i < goodUrls.size(); i++) {
			System.out.println(goodUrls.get(i));
			boolean result = urlVal.isValid(goodUrls.get(i));
			assertEquals(goodUrls.get(i), true, result);
		}

	}

	//test bad urls
	public void testBadUrls() throws IOException {
		//set up the validator
		UrlValidator urlVal = new UrlValidator(null, null, 1);
		List<String> badUrls = Files.readAllLines(new File("badUrls.txt").toPath(), Charset.defaultCharset());
		for (int i = 0; i < badUrls.size(); i++) {
			System.out.println(badUrls.get(i));
			boolean result = urlVal.isValid(badUrls.get(i));
			assertEquals(badUrls.get(i), false, result);
		}

	}

}