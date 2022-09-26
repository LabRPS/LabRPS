
#ifndef WLOBJECTDESCRIPTION_H
#define WLOBJECTDESCRIPTION_H

#include <QString>
#include "RPSUserDefinedPhenomenonAPIdefines.h"

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
	QString m_objectName;
	QString m_releaseDate;
	QString m_path;
	QString m_author;
	QString m_version;
	QString m_labRPSVersion;
	QString m_apiVersion;
	QString m_pluginVersion;

	bool operator==(const ObjectDescription  &rhs) const
	{
		return m_pluginName == rhs.m_pluginName &&
			   m_description == rhs.m_description &&
			   m_publicationTitle == rhs.m_publicationTitle &&
			   m_publicationLink == rhs.m_publicationLink &&
			   m_publicationAuthor == rhs.m_publicationAuthor &&
			   m_publicationDate == rhs.m_publicationDate &&
			   m_objectName == rhs.m_objectName &&
			   m_releaseDate == rhs.m_releaseDate &&
			   m_path == rhs.m_path &&
			   m_author == rhs.m_author &&
			   m_version == rhs.m_version &&
			   m_labRPSVersion == rhs.m_labRPSVersion &&
			   m_apiVersion == rhs.m_apiVersion &&
			   m_pluginVersion == rhs.m_pluginVersion;
	}
};

#endif  // WLOBJECTDESCRIPTION_H