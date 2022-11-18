#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class SyntaxHighlighter : public QSyntaxHighlighter {
  Q_OBJECT
 public:
  SyntaxHighlighter(QTextDocument *parent = nullptr);

 protected:
  void highlightBlock(const QString &text);

 private:
  struct HighlightingRule {
    QRegExp pattern;
    QTextCharFormat format;
  };

  QVector<HighlightingRule> highlightingRules;

  QRegExp commentStartExpression;
  QRegExp commentEndExpression;

  QTextCharFormat keywordFormat;
  QTextCharFormat classFormat;
  QTextCharFormat singleLineCommentFormat;
  QTextCharFormat multiLineCommentFormat;
  QTextCharFormat quotationFormat;
  QTextCharFormat singleQuotationFormat;
  QTextCharFormat functionFormat;

  QStringList keywords;
  QStringList uselessKeywords;
};

#endif // SYNTAXHIGHLIGHTER_H
