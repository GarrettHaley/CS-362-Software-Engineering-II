/**
 * Created by Garrett on 12/4/2017.
 */
import junit.framework.TestCase;
import java.util.Date;
import java.util.Random;
public class URLValidatorRandomTest extends TestCase {

    private boolean printStatus = false;
    private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
    private static int assertCheck = 0;
    public URLValidatorRandomTest(String testName) {
        super(testName);
    }

    public void testRandomIsValid()
    {
        System.out.println("Random testIsValid test:");
        ResultPair[][] testingOptions = getURLCombos();
        ResultPair[] schemeOptions = testingOptions [0], authorityOptions = testingOptions [1],
                portOptions = testingOptions [2], pathOptions = testingOptions [3], queryOptions = testingOptions [3];

        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertCheck = 0;
        Random rand = new Random();
        for(int cycle = 0; cycle<10000;cycle++) {
            int schemeIndex = rand.nextInt(schemeOptions.length);
            int authorityIndex = rand.nextInt(authorityOptions.length);
            int portIndex = rand.nextInt(portOptions.length);
            int pathIndex = rand.nextInt(pathOptions.length);
            int queryIndex = rand.nextInt(queryOptions.length);
            boolean expectedValidity = schemeOptions[schemeIndex].valid && authorityOptions[authorityIndex].valid && portOptions[portIndex].valid && pathOptions[pathIndex].valid && queryOptions[queryIndex].valid;
            String url = schemeOptions[schemeIndex].item + authorityOptions[authorityIndex].item + portOptions[portIndex].item + pathOptions[pathIndex].item + queryOptions[queryIndex].item;
            if (urlVal.isValid(url) != expectedValidity) {
                System.out.println("URL DID NOT VALIDATE CORRECTLY: " + url + " EXPECTED: " + expectedValidity + " ACTUAL: " + urlVal.isValid(url));
                assertCheck++;
            }
        }
        if(assertCheck > 0)
            fail("The testIsValid function has failed");
        else
            System.out.println("Success");
    }
    public static ResultPair[][] getURLCombos() {

        ResultPair[] testUrlScheme = {
                new ResultPair("http://", true),
                new ResultPair("ftp://", true),
                new ResultPair("https://", true),
                new ResultPair("ftps://", true),
                new ResultPair("telnet://", true),
                new ResultPair("h@@@ttp://", false),
                new ResultPair("95http://", false)
        };

        ResultPair[] testUrlAuthority = {
                new ResultPair("254.254.254.250", true),
                new ResultPair("www.multi-word-check.com", true),
                new ResultPair("www.gmail.com", true),
                new ResultPair("www.------------.com", false),
                new ResultPair("www-wrong-multi-format", false),
                new ResultPair("0.0.0.0.0", false)};

        ResultPair[] testUrlPort = {
                new ResultPair("", true),
                new ResultPair(":10", true),
                new ResultPair(":65535", true),
                new ResultPair(":%%%!!!$$", false),
                new ResultPair(":-1", false),
                new ResultPair(":letters", false)};

        ResultPair[] testPath = {
                new ResultPair("/first/goodpath", true),
                new ResultPair("/goodpath", true),
                new ResultPair("", true),
                new ResultPair("/good/path", true),
                new ResultPair("/wrong//path", false),
                new ResultPair("/............/", false),
                new ResultPair("//incorrectformatting", false)
        };

        ResultPair[] testUrlQuery = {
                new ResultPair("", true),
                new ResultPair("?q=100,10000", true),
                new ResultPair("?q=jdksh48935928slfkjd2lkfj", true),
                new ResultPair("!q=1", false)
        };

        ResultPair[][] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
        return testUrlParts;
    }
}
