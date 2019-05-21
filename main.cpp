#include <gtest/gtest.h>
#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<char, char> g_hashCharMap;

void upper_str(char *res)
{
    int i = 0;
    while (res[i] != '\0')
    {
        res[i] = toupper(res[i]);
        i++;
    }
}

int* countMod(const char str[])
{
    if (str == nullptr)
        return nullptr;

    int *res = new int[10];
    for (int i = 0; i < 10; ++i)
    {
        res[i] = 0;
    }

    int i = 0;
    int countNum = 0;
    int modIndex = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ')
        {
            countNum++;
        } else
        {
            res[modIndex++] = countNum;
            countNum = 0;
        }
        i++;
    }

    res[modIndex] = countNum;
    return res;
}

bool modCountCompare(int *cribCount, int *cipherTextCount)
{
    if (cribCount == nullptr || cipherTextCount == nullptr) return false;

    int i = 0;
    int j = 0;

    while (cribCount[i] != 0 && cipherTextCount[j] != 0)
    {
        if (cribCount[i] != cipherTextCount[j])
        {
            i = 0;
            j++;
        }
        else
        {
            i++;
        }
    }

    if (cribCount[i] == 0)
        return true;

    return false;
}

bool validCrib(const char ciphertext[], const char crib[])
{
    int *cribCount = countMod(crib);
    int *cipherTextCount = countMod(ciphertext);

    return modCountCompare(cribCount, cipherTextCount);
}

int findFirstCompareCharIndex(int *cribCount, int *cipherTextCount)
{
    int res = 0;

    int i = 0;
    int j = 0;

    while (cribCount[i] != 0 && cipherTextCount[j] != 0)
    {
        if (cribCount[i] != cipherTextCount[j])
        {
            i = 0;
            j++;
        }
        else
        {
            i++;
        }
    }

    for (int k = 0; k < j; k++ )
    {
        res += cipherTextCount[k] + 1;
    }

    return res;
}

void parseCribToHashMap(const char ciphertext[], const char crib[])
{
    int *cribCount = countMod(crib);
    int *cipherTextCount = countMod(ciphertext);

    int firstCharIndex = findFirstCompareCharIndex(cribCount, cipherTextCount);

    for (int i = 0, j = firstCharIndex; i < strlen(crib); i++,j++)
    {
        if (crib[i] == ' ') continue;
        g_hashCharMap[ciphertext[j]] = toupper(crib[i]);
    }
}

void generateResultString(char *res, const char ciphertext[])
{
    strcpy(res, ciphertext);

    for (int i = 0; i < strlen(res); i++)
    {
        if (g_hashCharMap.find(res[i]) != g_hashCharMap.end())
        {
            res[i] = g_hashCharMap[res[i]];
        }
    }

}

const char* decrypt(const char ciphertext[], const char crib[])
{
    char *res = new char[1000];

    if (validCrib(ciphertext, crib))
    {
        parseCribToHashMap(ciphertext, crib);
        generateResultString(res, ciphertext);
        return res;
    }
    else
    {
        return nullptr;
    }
}

TEST(SimpleTest, NullCipherTextSameCribReturnTrueAndReplace)
{
    EXPECT_EQ(nullptr, decrypt(nullptr, "nihao"));
}

TEST(SimpleTest, SameCipherTextSameCribReturnTrueAndReplace)
{
    EXPECT_STREQ("NIHAO", decrypt("nihao", "nihao"));
}

TEST(SimpleTest, LitterDiffCipherTextSameCribReturnTrueAndReplace)
{
    EXPECT_STREQ("NIHAO 2", decrypt("nihao 2", "nihao"));
}

TEST(SimpleTest, StartLitterDiffCipherTextSameCribReturnTrueAndReplace)
{
    EXPECT_STREQ("CAONM", decrypt("nihao", "caonm"));
}

TEST(SimpleTest, StartLitterDiff2CipherTextSameCribReturnTrueAndReplace)
{
    EXPECT_STREQ("kl CAONM kl", decrypt("kl nihao kl", "caonm"));
}

TEST(SimpleTest, StartLitterDiff3CipherTextSameCribReturnTrueAndReplace)
{
    EXPECT_STREQ("klC CAONM Mkl", decrypt("kln nihao okl", "caonm"));
}

