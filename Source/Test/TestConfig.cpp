#include <gtest/gtest.h>
#include <numeric>
#include <vector>

#include "../Config.h"

using namespace namelint;

namespace TargetIsGeneral {

TEST(GeneralOptions, Default) {
    Config config;

    //
    // General
    //
    std::vector<string> *pVect =
        &config.GetData()->General.Options.FileExtNameList;
    EXPECT_EQ(true, 3 == pVect->size());
    EXPECT_EQ(true,
              pVect->end() != std::find(pVect->begin(), pVect->end(), "*.c"));
    EXPECT_EQ(true,
              pVect->end() != std::find(pVect->begin(), pVect->end(), "*.h"));
    EXPECT_EQ(true,
              pVect->end() != std::find(pVect->begin(), pVect->end(), "*.cpp"));

    //
    // Rule
    //
    GeneralRules *pRule = &config.GetData()->General.Rules;
    EXPECT_EQ(RULETYPE::RULETYPE_DEFAULT, pRule->FileName);
    EXPECT_EQ(RULETYPE::RULETYPE_DEFAULT, pRule->FunctionName);
    EXPECT_EQ(RULETYPE::RULETYPE_DEFAULT, pRule->VariableName);

    //
    // WhiteList
    //
    // GeneralIgnoredList *pWhiteList = &config.GetData().m_WhiteList;
    // EXPECT_EQ(1, pWhiteList->IgnoredFuncPrefix.size());
    // EXPECT_EQ(1, pWhiteList->VariablePrefix.size());
}

TEST(GeneralOptions, Fake_General) {
    string content = "\
	[General] \r\n\
		ListFileExtName  = [\"*.a\",\"*.b\",\"*.c\",\"*.d\"] \r\n\
		BoolCheckVariableName = false \r\n\
		BoolCheckFunctionName = false \r\n\
		BoolCheckFileName	  = false \r\n\
	";

    Config config;
    bool bStatus = config.LoadStream(content);
    EXPECT_EQ(true, bStatus);

    GeneralOptions *pGeneral   = &config.GetData()->General.Options;
    std::vector<string> *pVect = &pGeneral->FileExtNameList;
    EXPECT_EQ(true, 4 == pVect->size());
    EXPECT_EQ(true,
              pVect->end() != std::find(pVect->begin(), pVect->end(), "*.a"));
    EXPECT_EQ(true,
              pVect->end() != std::find(pVect->begin(), pVect->end(), "*.b"));
    EXPECT_EQ(true,
              pVect->end() != std::find(pVect->begin(), pVect->end(), "*.c"));
    EXPECT_EQ(true,
              pVect->end() != std::find(pVect->begin(), pVect->end(), "*.d"));

    EXPECT_EQ(true, false == pGeneral->bCheckFileName);
    EXPECT_EQ(true, false == pGeneral->bCheckFunctionName);
    EXPECT_EQ(true, false == pGeneral->bCheckVariableName);
}

TEST(GeneralOptions, Fake_Rule) {
    string content = "\
	[Rule] \r\n\
		EnumFileName 	 = 3 \r\n\
		EnumFunctionName = 3 \r\n\
		EnumVariableName = 4 \r\n\
	";

    Config config;
    bool bStatus = config.LoadStream(content);
    EXPECT_EQ(true, bStatus);

    GeneralRules *pRule = &config.GetData()->General.Rules;
    EXPECT_EQ(RULETYPE::RULETYPE_LOWER_SNAKE, pRule->FileName);
    EXPECT_EQ(RULETYPE::RULETYPE_LOWER_SNAKE, pRule->FunctionName);
    EXPECT_EQ(RULETYPE::RULETYPE_HUNGARIAN, pRule->VariableName);
}

TEST(GeneralOptions, Fake_WhiteList) {
    //   string content = "\
	//[WhiteList] \r\n\
	//	ListFunctionPrefix 	 = [ \"_\", \"__\" ]    \r\n\
	//	ListVariablePrefix 	 = [ \"m_\", \"g_\" ]   \r\n\
	//	BoolAllowedUnderscopeChar = true            \r\n\
	//";

    //   Config config;
    //   bool bStatus = config.LoadStream(content);
    //   EXPECT_EQ(true, bStatus);

    //   GeneralIgnoredList *pWhiteList = &config.GetData().m_WhiteList;

    //   EXPECT_EQ(true, 2 == pWhiteList->IgnoredFuncPrefix.size());
    //   EXPECT_EQ(true, pWhiteList->IgnoredFuncPrefix.end() !=
    //                       std::find(pWhiteList->IgnoredFuncPrefix.begin(),
    //                                 pWhiteList->IgnoredFuncPrefix.end(),
    //                                 "_"));
    //   EXPECT_EQ(true, pWhiteList->IgnoredFuncPrefix.end() !=
    //                       std::find(pWhiteList->IgnoredFuncPrefix.begin(),
    //                                 pWhiteList->IgnoredFuncPrefix.end(),
    //                                 "__"));

    //   EXPECT_EQ(true, 2 == pWhiteList->IgnoredFuncPrefix.size());
    //   EXPECT_EQ(true, pWhiteList->VariablePrefix.end() !=
    //                       std::find(pWhiteList->VariablePrefix.begin(),
    //                                 pWhiteList->VariablePrefix.end(), "m_"));
    //   EXPECT_EQ(true, pWhiteList->VariablePrefix.end() !=
    //                       std::find(pWhiteList->VariablePrefix.begin(),
    //                                 pWhiteList->VariablePrefix.end(), "g_"));
}

} // namespace TargetIsGeneral