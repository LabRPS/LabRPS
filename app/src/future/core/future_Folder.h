#ifndef FUTURE_FOLDER_H
#define FUTURE_FOLDER_H

#include "core/AbstractAspect.h"

class QDomElement;

namespace future {
//! Folder in a project
class Folder : public AbstractAspect {
  Q_OBJECT

 public:
  Folder(const QString &name);

  virtual ~Folder();

  virtual QIcon icon() const;
  //! Return a new context menu.
  /**
   * The caller takes ownership of the menu.
   */
  virtual QMenu *createContextMenu() const;

  //! \name serialize/deserialize
  //@{
  //! Save as XML
  virtual void save(QXmlStreamWriter *, bool) const;
  //! Load from XML
  virtual bool load(XmlStreamReader *);
  bool load(QDomElement tablenode);

 protected:
  //! Read child aspect from XML
  bool readChildAspectElement(XmlStreamReader *reader);
  //@}
};
}  // namespace

#endif  // FUTURE_FOLDER_H
