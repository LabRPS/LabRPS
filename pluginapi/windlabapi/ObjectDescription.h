
#ifndef WLOBJECTDESCRIPTION_H
#define WLOBJECTDESCRIPTION_H

#include <QString>
#include "RPSWindLabAPIdefines.h"

class RPS_CORE_API ObjectDescription
{
public:
	ObjectDescription();
	~ObjectDescription();

	QString m_pluginName;
	QString m_description;
	QString m_publicationTitle;
	QString m_publicationLink;
	QString m_publicationAuthor;
	QString m_publicationDate;

	bool operator==(const ObjectDescription  &rhs) const
	{
		return m_pluginName == rhs.m_pluginName &&
			   m_description == rhs.m_description &&
			   m_publicationTitle == rhs.m_publicationTitle &&
			   m_publicationLink == rhs.m_publicationLink &&
			   m_publicationAuthor == rhs.m_publicationAuthor &&
			   m_publicationDate == rhs.m_publicationDate;
	}
};

#endif  // WLOBJECTDESCRIPTION_H