import junit.framework.TestCase;
import java.io.IOException;
import java.util.Random;

//based off of the original test implementation this class will unit test various urls against the known invalid tester

public class TeamRandomTest extends TestCase {

	//constructor
	public TeamRandomTest(String testName) {
		super(testName);
	}
	
	//random testing of urls
	public void testRandomUrls() throws IOException {
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String URL = "";
		StringBuilder URLBuffer = new StringBuilder();
		StringBuilder URLPathBuffer = new StringBuilder();
		int x, y, z;
		Random rand = new Random();
		boolean expected;
		System.out.println("Testing " + numTests + " random URLs.");

		//loop through the tests
		for(int i = 0; i < numTests; i++){
			//reset values
			expected = true;
			URLBuffer.setLength(0);
			URLPathBuffer.setLength(0);
			
			//determine if a valid or invalid URL scheme
			x = rand.nextInt(2);
			if (x == 0) { //valid URL Scheme
				y = rand.nextInt(2);
				URLBuffer.append(ValidURLScheme[y]);
			}
			else { //invalid URL Scheme
				expected = false;
				y = rand.nextInt(InvalidURLScheme.length);
				URLBuffer.append(InvalidURLScheme[y]);
			}
			
			//add host name
			//adding "www."?
			x = rand.nextInt(2);
			if (x == 0) { //add "www."
				URLBuffer.append("www.");
			}
			//add domain
			x = rand.nextInt(2);
			if (x == 0) { //use domain name
				y = rand.nextInt(30) + 1;
				for (int j = 0; j < y; j++) {
					z = rand.nextInt(URLchars.length());
					if (z > URLchars.indexOf('9')) { //invalid character for name
						expected = false;
					}
					URLBuffer.append(URLchars.charAt(z));
				}
			}
			else { // use IP address
				for (y = 0; y < 3; y++) {
					z = rand.nextInt(256);
					if (z > 255) { //invalid IP number
						expected = false;
					}
					URLBuffer.append(z + ".");
				}
				y = rand.nextInt(256);
				if (y > 255) { //invalid IP number
					expected = false;
				}
				URLBuffer.append(y);
			}
			//add TLD
			x = rand.nextInt(2);
			if (x == 0) { //valid TLD
				y = rand.nextInt(ValidURLTLD.length);
				URLBuffer.append(ValidURLTLD[y]);
			}
			else { //invalid TLD
				expected = false;
				y = rand.nextInt(InvalidURLTLD.length);
				URLBuffer.append(InvalidURLTLD[y]);
			}
			
			//add port
			x = rand.nextInt(2);
			if (x == 0) { //Add port number
				y = rand.nextInt(70000) - 100;
				if (y < 0 || y > 65535) {
					expected = false;
				}
				URLBuffer.append(":" + y);
			}
			
			//add path
			URLPathBuffer.append("/");
			x = rand.nextInt(100);
			for (int j = 0; j < x; j++) {
				y = rand.nextInt(URLpath.length());
				URLPathBuffer.append(URLpath.charAt(y));
			}
			
			//check if the path contains a space, "//", or ".."
			if (URLPathBuffer.toString().contains("//") || 
					URLPathBuffer.toString().contains("..") || 
					URLPathBuffer.toString().contains(" ")) {
				expected = false;
			}
			
			//add the path to the URL
			URLBuffer.append(URLPathBuffer.toString());
			
			//test the URL
			URL = URLBuffer.toString();
			
			//check if the URL is valid
			boolean result = urlVal.isValid(URL);
			if (result != expected) {
				System.out.println("\nTest Number " + (i + 1));
				System.out.println("URL: " + URL + "\nExpected: " + expected + " Result: " + result);
			}
			else {
				System.out.println("\nTest Number " + (i + 1));
				System.out.println("Passed URL: " + URL + "\nValidity: " + result);
			}
		}
	}
	
	int numTests = 5000;
	
	String ValidURLScheme[] = {"http://",
							   "https://",
							   "coap://",
							   "dns://",
							   "ftp://",
							   "ldap://",
							   "nfs://",
							   "shttp://"
	};
	
	String InvalidURLScheme[] = {"3bb://",
								 "2ada://",
								 "8ds:",
								 "4n://",
								 "net:/"
	};
	
	String URLchars = "abcdefghijklmnopqrstuvwxyz0123456789";
	
	String ValidURLTLD[] = {".com",
							".org",
							".net",
							".edu",
							".gov",
							".mil",
							".ae",
							".fj",
							".np",
							".uk"
	};
	
	String InvalidURLTLD[] = {".uv",
							  ".wa",
							  ".moc",
							  ".ra",
							  ".lo",
							  ".av",
							  ".vog",
							  ".ten"
	};
	
	String URLpath = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%";

}