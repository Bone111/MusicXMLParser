// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( Duration )
        MX_FORWARD_DECLARE_ELEMENT( EditorialGroup )
        MX_FORWARD_DECLARE_ELEMENT( Backup )

        inline BackupPtr makeBackup() { return std::make_shared<Backup>(); }

        class Backup : public ElementInterface
        {
        public:
            Backup();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;

            /* _________ Duration minOccurs = 1, maxOccurs = 1 _________ */
            DurationPtr getDuration() const;
            void setDuration( const DurationPtr& value );

            /* _________ EditorialGroup minOccurs = 1, maxOccurs = 1 _________ */
            EditorialGroupPtr getEditorialGroup() const;
            void setEditorialGroup( const EditorialGroupPtr& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            DurationPtr myDuration;
            EditorialGroupPtr myEditorialGroup;
        };
    }
}
