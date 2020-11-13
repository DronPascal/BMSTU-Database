#ifndef SQLHIGHLIGHTER_H
#define SQLHIGHLIGHTER_H
#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>
#include <QtGui>
#include <QFile>

class QTextDocument;

class SqlHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    SqlHighlighter(QTextDocument *parent = nullptr) : QSyntaxHighlighter(parent)
    {
        HighlightingRule rule;

        keywordFormat.setForeground(QColor(153,7,134));
        keywordFormat.setFontWeight(QFont::Bold);

        QStringList keywordPatterns;
                keywordPatterns << "\\bABSOLUTE\\b" << "\\bACTION\\b" << "\\bABORT\\b" << "\\bACTIVE\\b" << "\\bADD\\b" << "\\bAFTER\\b" << "\\bALL\\b" << "\\bALLOCATE\\b" << "\\bALTER\\b" << "\\bANALYZE\\b" << "\\bAND\\b" << "\\bANY\\b" << "\\bARE\\b" << "\\bAS\\b" << "\\bASCENDING\\b" << "\\bASSERTION\\b" << "\\bAT\\b" << "\\bAUTHORIZATION\\b" << "\\bAUTO\\b" << "\\bAUTO-INCREMENT\\b" << "\\bAUTOINC\\b" << "\\bAVG\\b" << "\\bBACKUP\\b" << "\\bBEFORE\\b" << "\\bBEGIN\\b" << "\\bBETWEEN\\b" << "\\bBIGINT\\b" << "\\bBINARY\\b" << "\\bBIT\\b" << "\\bBLOB\\b" << "\\bBOOLEAN\\b" << "\\bBOTH\\b" << "\\bBREAK\\b" << "\\bBROWSE\\b" << "\\bBULK\\b" << "\\bBY\\b" << "\\bBYTES\\b" << "\\bCACHE\\b" << "\\bCALL\\b" << "\\bCASCADE\\b" << "\\bCASCADED\\b" << "\\bCASE\\b" << "\\bCAST\\b" << "\\bCATALOG\\b" << "\\bCHANGE\\b" << "\\bCHAR\\b" << "\\bCHARACTER\\b" << "\\bCHARACTERJ^ENGTH\\b" << "\\bCHECK\\b" << "\\bCHECKPOINT\\b" << "\\bCLOSE\\b" << "\\bCLUSTER\\b" << "\\bCLUSTERED\\b" << "\\bCOALESCE\\b" << "\\bCOLLATE\\b" << "\\bCOLUMN\\b" << "\\bCOLUMNS\\b" << "\\bCOMMENT\\b" << "\\bCOMMIT\\b" << "\\bCOMMITTED\\b" << "\\bCOMPUTE\\b" << "\\bCOMPUTED\\b" << "\\bCONDITIONAL\\b" << "\\bCONFIRM\\b" << "\\bCONNECT\\b" << "\\bCONNECTION\\b" << "\\bCONSTRAINT\\b" << "\\bCONSTRAINTS\\b" << "\\bCONTAINING\\b" << "\\bCONTAINS\\b" << "\\bCONTAINSTABLE\\b" << "\\bCONTINUE\\b" << "\\bCONTROLROW\\b" << "\\bCONVERT\\b" << "\\bCOPY\\b" << "\\bCOUNT\\b" << "\\bCREATE\\b" << "\\bCROSS\\b" << "\\bCSTRING\\b" << "\\bCUBE\\b" << "\\bCURRENT\\b" << "\\bCURRENT_DATE\\b" << "\\bCURRENTJTIME\\b" << "\\bCURRENT_TIMESTAMP\\b" << "\\bCURRENT_USER\\b" << "\\bCURSOR\\b" << "\\bDATABASE\\b" << "\\bDATABASES\\b" << "\\bDATE\\b" << "\\bDATETIME\\b" << "\\bDAY\\b" << "\\bDBCC\\b" << "\\bDEALLOCATE DECIMAL\\b" << "\\bDEBUG DECLARE\\b" << "\\bDEC DEFAULT\\b" << "\\bDELETE\\b" << "\\bDENY\\b" << "\\bDESC\\b" << "\\bDESCENDING DISK\\b" << "\\bDIV\\b" << "\\bDESCRIBE DISTINCT DO\\b" << "\\bDISCONNECT DISTRIBUTED DOMAIN\\b" << "\\bDOUBLE\\b" << "\\bDROP\\b" << "\\bDUMMY\\b" << "\\bDUMP\\b" << "\\bELSE\\b" << "\\bELSEIF\\b" << "\\bENCLOSED\\b" << "\\bEND\\b" << "\\bERRLVL\\b" << "\\bERROREXIT\\b" << "\\bESCAPE\\b" << "\\bESCAPED\\b" << "\\bEXCEPT\\b" << "\\bEXCEPTION\\b" << "\\bEXEC\\b" << "\\bEXECUTE\\b" << "\\bEXISTS\\b" << "\\bEXIT\\b" << "\\bEXPLAIN\\b" << "\\bEXTEND\\b" << "\\bEXTERNAL\\b" << "\\bEXTRACT\\b" << "\\bFALSE\\b" << "\\bFETCH\\b" << "\\bFIELD\\b" << "\\bFIELDS\\b" << "\\bFILE\\b" << "\\bFILLFACTOR\\b" << "\\bFILTER\\b" << "\\bFLOAT\\b" << "\\bFLOPPY\\b" << "\\bFOR\\b" << "\\bFORCE\\b" << "\\bFOREIGN\\b" << "\\bFOUND\\b" << "\\bFREETEXT\\b" << "\\bFREETEXTTABLE\\b" << "\\bFROM\\b" << "\\bFULL\\b" << "\\bFUNCTION\\b" << "\\bGENERATOR\\b" << "\\bGET\\b" << "\\bGLOBAL\\b" << "\\bGO\\b" << "\\bGOTO\\b" << "\\bGRANT\\b" << "\\bGROUP\\b" << "\\bHAVING\\b" << "\\bHOLDLOCK\\b" << "\\bHOUR\\b" << "\\bIDENTITY\\b" << "\\bIF\\b" << "\\bIN\\b" << "\\bINACTIVE\\b" << "\\bINDEX\\b" << "\\bINDICATOR\\b" << "\\bINFILE\\b" << "\\bINNER\\b" << "\\bINOUT\\b" << "\\bINPUT\\b" << "\\bINSENSITIVE\\b" << "\\bINSERT\\b" << "\\bINT\\b" << "\\bINTEGER\\b" << "\\bINTERSECT\\b" << "\\bINTERVAL\\b" << "\\bINTO\\b" << "\\bIS\\b" << "\\bISOLATION\\b" << "\\bJOIN\\b" << "\\bKEY\\b" << "\\bKILL\\b" << "\\bLANGUAGE\\b" << "\\bLAST\\b" << "\\bLEADING\\b" << "\\bLEFT\\b" << "\\bLENGTH\\b" << "\\bLEVEL\\b" << "\\bLIKE\\b" << "\\bLIMIT\\b" << "\\bLINENO\\b" << "\\bLINES\\b" << "\\bLISTEN\\b" << "\\bLOAD\\b" << "\\bLOCAL\\b" << "\\bLOCK\\b" << "\\bLOGFILE\\b" << "\\bLONG\\b" << "\\bLOWER\\b" << "\\bMANUAL\\b" << "\\bMATCH\\b" << "\\bMAX\\b" << "\\bMERGE\\b" << "\\bMESSAGE\\b" << "\\bMIN\\b" << "\\bMINUTE\\b" << "\\bMIRROREXIT\\b" << "\\bMODULE\\b" << "\\bMONEY\\b" << "\\bMONTH\\b" << "\\bMOVE\\b" << "\\bNAMES\\b" << "\\bNATIONAL\\b" << "\\bNATURAL\\b" << "\\bNCHAR\\b" << "\\bNEXT\\b" << "\\bNEW\\b" << "\\bNO\\b" << "\\bNOCHECK\\b" << "\\bNONCLUSTERED\\b" << "\\bNONE\\b" << "\\bNOT\\b" << "\\bNULL\\b" << "\\bNULLIF\\b" << "\\bNUMERIC\\b" << "\\bOF\\b" << "\\bOFF\\b" << "\\bOFFSET\\b" << "\\bOFFSETS\\b" << "\\bON\\b" << "\\bONCE\\b" << "\\bONLY\\b" << "\\bOPEN\\b" << "\\bOPTION\\b" << "\\bOR\\b" << "\\bORDER\\b" << "\\bOUTER\\b" << "\\bOUTPUT\\b" << "\\bOVER\\b" << "\\bOVERFLOW\\b" << "\\bOVERLAPS\\b" << "\\bPAD\\b" << "\\bPAGE\\b" << "\\bPAGES\\b" << "\\bPARAMETER\\b" << "\\bPARTIAL\\b" << "\\bPASSWORD\\b" << "\\bPERCENT\\b" << "\\bPERM\\b" << "\\bPERMANENT\\b" << "\\bPIPE\\b" << "\\bPLAN\\b" << "\\bPOSITION\\b" << "\\bPRECISION\\b" << "\\bPREPARE\\b" << "\\bPRIMARY\\b" << "\\bPRINT\\b" << "\\bPRIOR\\b" << "\\bPRIVILEGES\\b" << "\\bPROC\\b" << "\\bPROCEDURE\\b" << "\\bPROCESSEXIT\\b" << "\\bPROTECTED\\b" << "\\bPUBLIC\\b" << "\\bPURGE\\b" << "\\bRAISERROR\\b" << "\\bREAD\\b" << "\\bREADTEXT\\b" << "\\bREAL\\b" << "\\bREFERENCES\\b" << "\\bREGEXP\\b" << "\\bRELATIVE\\b" << "\\bRENAME\\b" << "\\bREPEAT\\b" << "\\bREPLACE\\b" << "\\bREPLICATION\\b" << "\\bREQUIRE\\b" << "\\bRESERV\\b" << "\\bRESERVING\\b" << "\\bRESET\\b" << "\\bRESTORE\\b" << "\\bRESTRICT\\b" << "\\bRETAIN\\b" << "\\bRETURN\\b" << "\\bRETURNS\\b" << "\\bREVOKE\\b" << "\\bRIGHT\\b" << "\\bROLLBACK\\b" << "\\bROLLUP\\b" << "\\bROWCOUNT\\b" << "\\bRULE\\b" << "\\bSAVE\\b" << "\\bSAVEPOINT\\b" << "\\bSCHEMA\\b" << "\\bSECOND\\b" << "\\bSECTION\\b" << "\\bSEGMENT\\b" << "\\bSELECT\\b" << "\\bSENSITIVE\\b" << "\\bSEPARATOR\\b" << "\\bSEQUENCE\\b" << "\\bSESSION_USER\\b" << "\\bSET\\b" << "\\bSETUSER\\b" << "\\bSHADOW\\b" << "\\bSHARED\\b" << "\\bSHOW\\b" << "\\bSHUTDOWN\\b" << "\\bSINGULAR\\b" << "\\bSIZE\\b" << "\\bSMALLINT\\b" << "\\bSNAPSHOT\\b" << "\\bSOME\\b" << "\\bSORT\\b" << "\\bSPACE\\b" << "\\bSQL\\b" << "\\bSQLCODE\\b" << "\\bSQLERROR\\b" << "\\bSTABILITY\\b" << "\\bSTARTING\\b" << "\\bSTARTS\\b" << "\\bSTATISTICS\\b" << "\\bSUBSTRING\\b" << "\\bSUM\\b" << "\\bSUSPEND\\b" << "\\bTABLE\\b" << "\\bTABLES\\b" << "\\bTAPE\\b" << "\\bTEMP\\b" << "\\bTEMPORARY\\b" << "\\bTHEN\\b" << "\\bTO\\b" << "\\bTRAN\\b" << "\\bTRIGGER\\b" << "\\bTRUNCATE\\b" << "\\bUNIQUE\\b" << "\\bUPDATETEXT\\b" << "\\bUSE\\b" << "\\bVALUE\\b" << "\\bVARIABLE\\b" << "\\bVIEW\\b" << "\\bWAITFOR\\b" << "\\bWHILE\\b" << "\\bWRITE\\b" << "\\bYEAR\\b" << "\\bTEXT\\b" << "\\bTIME\\b" << "\\bTOP\\b" << "\\bTRANSACTION\\b" << "\\bTRIM\\b" << "\\bUNCOMMITTED\\b" << "\\bUNTIL\\b" << "\\bUPPER\\b" << "\\bUSER\\b" << "\\bVALUES\\b" << "\\bVARYING\\b" << "\\bVOLUME\\b" << "\\bWHEN\\b" << "\\bWITH\\b" << "\\bWRITETEXT\\b" << "\\bZONE\\b" << "\\bTEXTSIZE\\b" << "\\bTIMESTAMP\\b" << "\\bTRAILING\\b" << "\\bTRANSLATE\\b" << "\\bTRUE\\b" << "\\bUNION\\b" << "\\bUPDATE\\b" << "\\bUSAGE\\b" << "\\bUSING\\b" << "\\bVARCHAR\\b" << "\\bVERBOSE\\b" << "\\bWAIT\\b" << "\\bWHERE\\b" << "\\bWORK\\b" << "\\bXOR\\b";
        foreach (const QString &pattern, keywordPatterns) {
            rule.pattern = QRegExp(pattern);
            rule.format = keywordFormat;
            highlightingRules.append(rule);
        }

        singleLineCommentFormat.setForeground(Qt::darkGreen);
        rule.pattern = QRegExp("//[^\n]*");
        rule.format = singleLineCommentFormat;
        highlightingRules.append(rule);

        multiLineCommentFormat.setForeground(Qt::darkGreen);

        quotationFormat.setForeground(QColor(192,70,67));
        rule.pattern = QRegExp("'[^']*'");
        rule.format = quotationFormat;
        highlightingRules.append(rule);

        functionFormat.setForeground(QColor(153,7,134));
        rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
        rule.format = functionFormat;
        highlightingRules.append(rule);

        commentStartExpression = QRegExp("/\\*");
        commentEndExpression = QRegExp("\\*/");
    }

protected:
    void highlightBlock(const QString &text)
    {
        foreach (const HighlightingRule &rule, highlightingRules) {
            QRegExp expression(rule.pattern);
            int index = expression.indexIn(text.toUpper());
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, rule.format);
                index = expression.indexIn(text.toUpper(), index + length);
            }
        }
        setCurrentBlockState(0);

        int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = commentStartExpression.indexIn(text.toUpper());

        while (startIndex >= 0) {
            int endIndex = commentEndExpression.indexIn(text.toUpper(), startIndex);
            int commentLength;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex
                                + commentEndExpression.matchedLength();
            }
            setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = commentStartExpression.indexIn(text.toUpper(), startIndex + commentLength);
        }
    }

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};
#endif // SQLHIGHLIGHTER_H
