#ifndef ASPECT_PRIVATE_H
#define ASPECT_PRIVATE_H

#include "AbstractAspect.h"

#include <QString>
#include <QDateTime>
#include <QList>
#include <QSettings>
#include <QHash>

//! Private data managed by AbstractAspect.
class AbstractAspect::Private {
 public:
  Private(AbstractAspect *owner, const QString &name);
  ~Private();

  void addChild(AbstractAspect *child);
  void insertChild(int index, AbstractAspect *child);
  int indexOfChild(const AbstractAspect *child) const;
  int removeChild(AbstractAspect *child);
  int childCount() const;
  AbstractAspect *child(int index);

  QString name() const;
  void setName(const QString &value);
  QString comment() const;
  void setComment(const QString &value);
  QString captionSpec() const;
  void setCaptionSpec(const QString &value);
  QDateTime creationTime() const;
  void setCreationTime(const QDateTime &time);

  QString caption() const;
  AbstractAspect *owner() { return d_owner; }
  AbstractAspect *parent() { return d_parent; }

  QString uniqueNameFor(const QString &current_name) const;

  static QSettings *g_settings;
  static QHash<QString, QVariant> g_defaults;

 private:
  static int indexOfMatchingBrace(const QString &str, int start);
  QList<AbstractAspect *> d_children;
  QString d_name, d_comment, d_caption_spec;
  QDateTime d_creation_time;
  AbstractAspect *d_owner;
  AbstractAspect *d_parent;
};

#endif  // ASPECT_PRIVATE_H
