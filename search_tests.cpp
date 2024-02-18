#include <gtest/gtest.h>

#include "search.h"
#include "tests/build_index.h"
#include "tests/clean_token.h"
#include "tests/find_query_matches.h"
#include "tests/gather_tokens.h"

/**********************/
//CLEAN TOKEN TESTS
/**********************/

//Tokens with punctuation at both the beginning and end
TEST(CleanToken, DoublePunctuationCleaning) {
    map<string, set<string>> tests;

    tests["hello"].insert(".HELLO.");
    tests["hello"].insert("!.?heLlo...");
    tests["hello"].insert(".\"hellO.\"!?");
    tests["hello"].insert(".HELLO.");
    tests["hello"].insert("...Hello......!");
    tests["hello"].insert(".\"!?heLLo!.\".\"!");

    testCleanToken(tests);
}

//Tokens with punctuation in the middle, as well as possibly at the ends
TEST(CleanToken, PunctuationInside) {
    map<string, set<string>> tests;

    tests["hel.lo"].insert("HEL.LO");
    tests["h.e.llo"].insert("h.e.Llo.");
    tests["he!ll?o"].insert("he!ll?O");
    tests["he!llo"].insert(".HE!LLO");
    tests["he!ll.o"].insert("..He!ll.o");
    tests["hell.?o"].insert(".!?heLL.?o!");

    testCleanToken(tests);
}

//Tokens with numbers at end
TEST(CleanToken, NumberAtEnds) {
    map<string, set<string>> tests;

    tests["1hello"].insert("1hello");
    tests["hello23"].insert("HeLLO23");
    tests["1hello3"].insert("1Hello3");

    testCleanToken(tests);
}

//Tokens one letter long
TEST(CleanToken, OneLetter) {
    map<string, set<string>> tests;

    tests["x"].insert("x");
    tests["y"].insert("Y");

    testCleanToken(tests);
}

//Tokens with a lot of punctuation
TEST(CleanToken, LotsOfPunct) {
    map<string, set<string>> tests;

    tests["hello"].insert(".....................hello");
    tests["hello"].insert("hello..............!");
    tests["hello"].insert("!!!!!!!!!!!!!!.....hello!!!......");

    testCleanToken(tests);
}

//Tokens that start or end with non-punct, non-letter, non-digit
TEST(CleanToken, WeirdEnds) {
    map<string, set<string>> tests;

    tests["hello"].insert("\"hello");
    tests["hello"].insert("hello\"");
    tests["hello"].insert("\"hello\"");

    testCleanToken(tests);
}

/**********************/
//GATHER TOKENS TESTS
/**********************/

//Text with leading spaces
TEST(GatherTokens, LeadingSpaces) {
    string text = "                   I'm not trying to eat you!";
    set<string> expected = {"i'm", "not", "trying", "to", "eat", "you"};
    set<string> studentResult = gatherTokens(text);

    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

//Text with trailing spaces
TEST(GatherTokens, TrailingSpaces) {
    string text = "I'm not trying to eat you!        ";
    set<string> expected = {"i'm", "not", "trying", "to", "eat", "you"};
    set<string> studentResult = gatherTokens(text);

    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

//Text with multiple spaces between words
TEST(GatherTokens, MultipleSpaces) {
    string text = "I'm   not   trying  to  eat   you!";
    set<string> expected = {"i'm", "not", "trying", "to", "eat", "you"};
    set<string> studentResult = gatherTokens(text);

    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

/****************************/
//BUILD INDEX
/****************************/

//TinyTxt Test
TEST(BuildIndex, TinyTxt) {
    string filename = "tiny.txt";
    map<string, set<string>> expected = {
        {"eggs", {"www.shoppinglist.com"}},
        {"milk", {"www.shoppinglist.com"}},
        {"fish", {"www.shoppinglist.com", "www.dr.seuss.net"}},
        {"red", {"www.rainbow.org", "www.dr.seuss.net"}},
        {"bread", {"www.shoppinglist.com"}},
        {"cheese", {"www.shoppinglist.com"}},
        {"green", {"www.rainbow.org"}},
        {"orange", {"www.rainbow.org"}},
        {"yellow", {"www.rainbow.org"}},
        {"blue", {"www.rainbow.org", "www.dr.seuss.net"}},
        {"indigo", {"www.rainbow.org"}},
        {"violet", {"www.rainbow.org"}},
        {"one", {"www.dr.seuss.net"}},
        {"two", {"www.dr.seuss.net"}},
        {"i'm", {"www.bigbadwolf.com"}},
        {"not", {"www.bigbadwolf.com"}},
        {"trying", {"www.bigbadwolf.com"}},
        {"to", {"www.bigbadwolf.com"}},
        {"eat", {"www.bigbadwolf.com"}},
        {"you", {"www.bigbadwolf.com"}}
    };
    map<string, set<string>> studentIndex;
    int studentNumProcesed = buildIndex(filename, studentIndex);

    string indexTestFeedback = "buildIndex(\"" + filename + "\", ...) index incorrect\n";
    EXPECT_EQ(expected, studentIndex) << indexTestFeedback;

    string retTestFeedback = "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
    EXPECT_EQ(4, studentNumProcesed) << retTestFeedback;
}

//File not found test

TEST(BuildIndex, unknownFile) {
    string filename = "fileThatDoesntExist.txt";
    map<string, set<string>> expected;

    map<string, set<string>> studentIndex;
    int studentNumProcesed = buildIndex(filename, studentIndex);

    string indexTestFeedback = "buildIndex(\"" + filename + "\", ...) index incorrect\n";
    EXPECT_EQ(expected, studentIndex) << indexTestFeedback;

    string retTestFeedback = "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
    EXPECT_EQ(0, studentNumProcesed) << retTestFeedback;
}

/****************************/
//Find Query Matches Tests
/****************************/

TEST(FindQueryMatches, QueryNotFound) {
    set<string> expected;

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "unknown"));
    EXPECT_EQ(expected, findQueryMatches(INDEX, "bruh"));
}

TEST(FindQueryMatches, LateQueryNotFound) {
    set<string> expected;

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "there hello all +bruh"));
    EXPECT_EQ(expected, findQueryMatches(INDEX, "all laws of aviation +a +puzzle"));
}

TEST(FindQueryMatches, LateIntersectionNotFound) {
    set<string> expected;

    expected = { "example.com", "random.org", "uic.edu" };
    EXPECT_EQ(expected, findQueryMatches(INDEX, "there hello all -bruh"));
}

TEST(FindQueryMatches, LateUnmodifiedNotFound) {
    set<string> expected;

    expected = { "example.com", "random.org", "uic.edu" };
    EXPECT_EQ(expected, findQueryMatches(INDEX, "there hello all bruh"));
}