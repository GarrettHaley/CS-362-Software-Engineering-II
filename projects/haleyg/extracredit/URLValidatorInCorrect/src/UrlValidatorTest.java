/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {

    private boolean printStatus = false;
    private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
    private static int assertCheck = 0;
    public UrlValidatorTest(String testName) {
        super(testName);
    }

    static public void assertFalse(String message, boolean validate){
        if(validate != false) {
            System.out.println("Error: " + message);
            assertCheck++;
        }
    }
    static public void assertTrue(String message, boolean validate){
        if(validate != true) {
            System.out.println("Error: " + message);
            assertCheck++;
        }
    }
    public void testManualTest()
    {
        System.out.println("Manual tests:");
        assertCheck = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        assertFalse("This URL should not validate: http://www.gmail.com:-50",urlVal.isValid("http://www.gmail.com:-50"));
        assertFalse("This URL should not validate: http://gmail.com/new//",urlVal.isValid("http://gmail.com/new//"));
        assertFalse("This URL should not validate: http://gm<><>ail.com/here",urlVal.isValid("http://gm<><>ail.com/here"));
        assertFalse("This URL should not validate: http:/gmail.com",urlVal.isValid("http:/gmail.com"));
        assertFalse("This URL should not validate: ://gmail.com",urlVal.isValid("://gmail.com"));
        assertFalse("This URL should not validate: 12htp://www.gmail.com",urlVal.isValid("12htp://www.gmail.com"));
        assertFalse("This URL should not validate: http://gmail.com/...",urlVal.isValid("http://gmail.com/..."));
        assertFalse("This URL should not validate: http://257.257.257.257:90/testing?test=thetest",urlVal.isValid("http://256.256.256.256:80/test1?action=view"));

        assertTrue("This URL should validate: https://www.gmail.com",urlVal.isValid("https://www.gmail.com"));
        assertTrue("This URL should validate: http://www.12345.com",urlVal.isValid("http://www.12345.com"));
        assertTrue("This URL should validate: http://www.gmail.com/!",urlVal.isValid("http://www.gmail.com/!"));
        assertTrue("This URL should validate: http://www.gmail.com/#$?$#",urlVal.isValid("http://www.gmail.com/#$?$#"));
        assertTrue("This URL should validate: http://www.gmail.com/?newAction=viewnextItem",urlVal.isValid("http://www.gmail.com/?newAction=viewnextItem"));
        assertTrue("This URL should validate: http://gmail.com/$location",urlVal.isValid("http://gmail.com/$location"));
        assertTrue("This URL should validate: http://gmail.com/newlocation?/",urlVal.isValid("http://gmail.com/newlocation?/"));
        assertTrue("This URL should validate: http://www.gmail.com:10",urlVal.isValid("http://www.gmail.com:10"));
        assertTrue("This URL should validate: http://www.gmail.com:10000",urlVal.isValid("http://www.gmail.com:10000"));

        if(assertCheck > 0)
            fail("The manual tests have failed");
        else
            System.out.println("Success");
    }


    public void testYourFirstPartition(){//PARTITION 1: SCHEME
        System.out.println("Scheme tests:");
        assertCheck = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        assertFalse("This scheme should not validate: h@@@ttp://www.gmail.com",urlVal.isValid("h@@@ttp://www.gmail.com"));
        assertFalse("This scheme should not validate: 95http://www.gmail.com",urlVal.isValid("95http://www.gmail.com"));
        assertFalse("This scheme should not validate: 00http://www.gmail.com",urlVal.isValid("00http://www.gmail.com"));

        assertTrue("This scheme should validate: http://www.gmail.com",urlVal.isValid("http://www.gmail.com"));
        assertTrue("This scheme should validate: ftp://www.gmail.com",urlVal.isValid("ftp://www.gmail.com"));
        assertTrue("This scheme should validate: https://www.gmail.com",urlVal.isValid("https://www.gmail.com"));
        assertTrue("This scheme should validate: ftps://www.gmail.com",urlVal.isValid("ftps://www.gmail.com"));
        assertTrue("This scheme should validate: telnet://www.gmail.com",urlVal.isValid("telnet://www.gmail.com"));

        if(assertCheck > 0)
            fail("The scheme partitioned tests have failed");
        else
            System.out.println("Success");
    }

    public void testYourSecondPartition(){//PARTITION 2: Authority
        System.out.println("Authority tests:");
        assertCheck = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertFalse("This authority should not validate: http://www-wrong-multi-format",urlVal.isValid("http://www-wrong-multi-format"));
        assertFalse("This authority should not validate: http://www.------------.com",urlVal.isValid("http://www.------------.com"));
        assertFalse("This authority should not validate: http://.dotcheck",urlVal.isValid("http://.dotcheck"));
        assertFalse("This authority should not validate: http://www/incorrectslash/edu",urlVal.isValid("http://www/incorrectslash/edu"));
        assertFalse("This authority should not validate: http://www.10:1:00:10",urlVal.isValid("http://www.10:1:00:10"));
        assertFalse("This authority should not validate: http://0.0.0.0.0",urlVal.isValid("http://0.0.0.0.0"));
        assertFalse("This authority should not validate: http://0.0.1",urlVal.isValid("http://0.0.1"));
        assertFalse("This URL should not validate: http://257.257.257.257:90/testing?test=thetest",urlVal.isValid("http://256.256.256.256:80/test1?action=view"));
        assertFalse("This URL should not validate: http://300.300.300.300:90/testing?test=thetest",urlVal.isValid("http://300.300.300.300:80/test1?action=view"));

        assertTrue("This authority should not validate: http://www.gmail.edu",urlVal.isValid("http://www.gmail.edu"));
        assertTrue("This authority should validate: http://www.multi-word-check.com",urlVal.isValid("http://www.multi-word-check.com"));
        assertTrue("This authority should validate: http://docs.checkProperFromat.com",urlVal.isValid("http://docs.checkProperFromat.com"));
        assertTrue("This authority should validate: http://254.254.254.250",urlVal.isValid("http://254.254.254.250"));

        if(assertCheck > 0)
            fail("The authority partitioned tests have failed");
        else
            System.out.println("Success");
    }

    public void testYourThirdPartition() {//PARTITION 3: PORT
        System.out.println("Port tests:");
        assertCheck = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        assertFalse("This port should not validate: http://www.gmail.com:%%%!!!$$",urlVal.isValid("http://www.gmail.com:%%%!!!$$"));
        assertFalse("This port should not validate: http://www.gmail.com:letters",urlVal.isValid("http://www.gmail.com:letters"));
        assertFalse("This port should not validate: http://www.gmail.com:-1",urlVal.isValid("http://www.gmail.com:-1"));
        assertFalse("This port should not validate: http://www.gmail.com:-10000000",urlVal.isValid("http://www.gmail.com:-10000000"));
        assertFalse("This port should not validate: http://www.gmail.com:10000000",urlVal.isValid("http://www.gmail.com:10000000"));

        assertTrue("This port should validate: http://www.gmail.com:0",urlVal.isValid("http://www.gmail.com:0"));
        assertTrue("This port should validate: http://www.gmail.com:1",urlVal.isValid("http://www.gmail.com:1"));
        assertTrue("This port should validate: http://www.gmail.com:1000",urlVal.isValid("http://www.gmail.com:1000"));
        assertTrue("This port should validate: http://www.gmail.com:10000",urlVal.isValid("http://www.gmail.com:10000"));
        assertTrue("This port should validate: http://www.gmail.com:555",urlVal.isValid("http://www.gmail.com:555"));

        if(assertCheck > 0)
            fail("The port partitioned tests have failed");
        else
            System.out.println("Success");
    }

    public void testYourFourthPartition() {//PARTITION 4: PATH
        System.out.println("Path tests:");
        assertCheck = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        assertFalse("This path should not validate: http://www.gmail.com/wrong//path",urlVal.isValid("http://www.gmail.com/wrong//path"));
        assertFalse("This path should not validate: http://www.gmail.com/............/",urlVal.isValid("http://www.gmail.com/............/"));
        assertFalse("This path should not validate: http://www.gmail.com:",urlVal.isValid("http://www.gmail.com:"));
        assertFalse("This path should not validate: http://www.gmail.coma.99",urlVal.isValid("http://www.gmail.coma.99"));
        assertFalse("This path should not validate: http://www.gmail.com//incorrectformatting",urlVal.isValid("http://www.gmail.com//incorrectformatting"));
        assertFalse("This path should not validate: http://www.gmail.com/incorrect \\n /path",urlVal.isValid("http://www.gmail.com/incorrect \\n /path"));

        assertTrue("This path should validate: http://www.gmail.com/first/goodpath",urlVal.isValid("http://www.gmail.com/first/goodpath"));
        assertTrue("This path should validate: http://www.gmail.com/good/path#",urlVal.isValid("http://www.gmail.com/good/path#"));
        assertTrue("This path should validate: http://www.gmail.com/anothergoodpath99",urlVal.isValid("http://www.gmail.com/anothergoodpath99"));
        assertTrue("This path should validate: http://www.gmail.com",urlVal.isValid("http://www.gmail.com"));
        assertTrue("This path should validate: http://www.gmail.com/99/LastTestingGoodpath",urlVal.isValid("http://www.gmail.com/99/LastTestingGoodpath"));

        if(assertCheck > 0)
            fail("The path partitioned tests have failed");
        else
            System.out.println("Success");
    }

    public void testYourFifthParition() {//PARTITION 5: QUERIES
        System.out.println("Query tests:");
        assertCheck = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        assertFalse("This query should not validate: http://www.gmail.com:q=1",urlVal.isValid("http://www.gmail.com:q=1"));
        assertFalse("This query should not validate: http://www.gmail.com!q=1",urlVal.isValid("http://www.gmail.com!q=1"));
        assertFalse("This query should not validate: http://www.gmail.comq=1",urlVal.isValid("http://www.gmail.comq=1"));
        assertFalse("This query should not validate: http://www.gmail.com   q=1",urlVal.isValid("http://www.gmail.com   q=1"));

        assertTrue("This query should validate: http://www.gmail.com?    ?   q=1",urlVal.isValid("http://www.gmail.com?    ?   q=1"));
        assertTrue("This query should validate: http://www.gmail.com?goodQUERY=LOOK&HERE=LOOKHERE",urlVal.isValid("http://www.gmail.com?goodQUERY=LOOK&HERE=LOOKHERE"));
        assertTrue("This query should validate: http://www.gmail.com?q=100,10000",urlVal.isValid("http://www.gmail.com?q=100,10000"));
        assertTrue("This query should validate: http://www.gmail.com?q=1;1000;10000",urlVal.isValid("http://www.gmail.com?q=1;1000;10000"));
        assertTrue("This query should validate: http://www.gmail.com?q=jdksh48935928slfkjd2lkfj",urlVal.isValid("http://www.gmail.com?q=jdksh48935928slfkjd2lkfj"));
        if(assertCheck > 0)
            fail("The query partitioned tests have failed");
        else
            System.out.println("Success");
    }

    public void testIsValid()
    {
        System.out.println("testIsValid tests:");
        ResultPair[][] testingOptions = getURLCombos();
        ResultPair[] schemeOptions = testingOptions [0], authorityOptions = testingOptions [1],
                portOptions = testingOptions [2], pathOptions = testingOptions [3], queryOptions = testingOptions [3];

        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertCheck = 0;
        for (int x = 0; x < schemeOptions.length; x++) {
            for (int y = 0; y < authorityOptions.length; y++) {
                for (int z = 0; z < portOptions.length; z++) {
                    for (int i = 0; i < pathOptions.length; i++) {
                        for (int j = 0; j < queryOptions.length; j++) {
                            boolean expectedValidity = schemeOptions[x].valid && authorityOptions[y].valid && portOptions[z].valid && pathOptions[i].valid && queryOptions[j].valid;
                            String url = schemeOptions[x].item+authorityOptions[y].item+portOptions[z].item+pathOptions[i].item+queryOptions[j].item;
                            if(urlVal.isValid(url) != expectedValidity) {
                                System.out.println("URL DID NOT VALIDATE CORRECTLY: "+url+" EXPECTED: "+ expectedValidity + " ACTUAL: "+ urlVal.isValid(url));
                                assertCheck++;
                            }
                        }
                    }
                }
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
                new ResultPair("256.256.256.256", false),
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
