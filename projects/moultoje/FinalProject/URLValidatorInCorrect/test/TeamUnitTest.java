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
		try {
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
			List<String> goodUrls = Files.readAllLines(new File("goodUrls.txt").toPath(), Charset.defaultCharset());
			System.out.println("Testing: " + goodUrls.size() + " good URLS");
			int count = 0;
			for (int i = 0; i < goodUrls.size(); i++) {
				//System.out.println(i+1);
				//System.out.println((i + 1) + ":  " + goodUrls.get(i));
				
				boolean result = urlVal.isValid(goodUrls.get(i));
				try {
					assertEquals(goodUrls.get(i), true, result);	
					count++;
				}
				catch (Exception e)
				{
					System.out.println(e.toString());
				}
			}
			System.out.println("Completed: " + count + " good URLS");
		}
		catch (Exception e) {
			System.out.println(e.toString());
		}
		
		

	}

	//test bad urls
	public void testBadUrls() throws IOException {
		//set up the validator
	
		try {
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
			List<String> badUrls = Files.readAllLines(new File("badUrls.txt").toPath(), Charset.defaultCharset());
			System.out.println("Testing: " + badUrls.size() + " bad URLS");
			int count = 0;
			for (int i = 0; i < badUrls.size(); i++) {
				//System.out.println(i+1);
				//System.out.println((i + 1) + ":  " + badUrls.get(i));
				
				boolean result = urlVal.isValid(badUrls.get(i));
				try {
					assertEquals(badUrls.get(i), false, result);	
					count++;
				}
				catch (Exception e)
				{
					System.out.println(e.toString());
				}
			}
			System.out.println("Completed: " + count + " bad URLS");
		}
		catch (Exception e) {
			System.out.println(e.toString());
		}

	}
	
	//Test a null URL
	public void testNull() throws IOException {
		//set up the validator
		try {
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
			String url = null;
			
			boolean result = urlVal.isValid(url);
			
			try {
				assertEquals(url, false, result);
			}
			catch(Exception e)
			{
				System.out.println(e.toString());
			}
			System.out.println("Null passed to isValid and false returned successful");
		}
		catch(Exception e)
		{
			System.out.println(e.toString());
		}
	}

	//Testing fragments in URLs
	public void testFragment() throws IOException {
		//URL without frags
		try {
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
			String urlWithoutFrags = "http://www.amazon.com";
			
			boolean result = urlVal.isValid(urlWithoutFrags);
			
			try {
				assertEquals(urlWithoutFrags, true, result);
			}
			catch(Exception e)
			{
				System.out.println(e.toString());
			}
			System.out.println("URL without frags passed. Test successful");
		}
		catch(Exception e)
		{
			System.out.println(e.toString());
		}
		
		//URL with frags
		try {
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
			String urlWithFrags = "http://wwww.amazon.com/#Frag";
			
			boolean result = urlVal.isValid(urlWithFrags);
			
			try {
				assertEquals(urlWithFrags, false, result);
			}
			catch(Exception e)
			{
				System.out.println(e.toString());
			}
			System.out.println("URL with frags passed and failed return. Test successful");
		}
		catch(Exception e)
		{
			System.out.println(e.toString());
		}
	}

}