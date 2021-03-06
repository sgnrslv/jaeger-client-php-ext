#include <iostream>
#include "Tag.h"
#include "Tracer.h"

const std::string OpenTracing::Tag::TAG_TYPE_HOST{ "host" };
const std::string OpenTracing::Tag::TAG_TYPE_IP{ "ip" };

OpenTracing::Tag::Tag(const std::string& key, const bool& value) :
    _key{ key },
    _vType{ jaegertracing::thrift::TagType::BOOL },
    _vBool{ value },
    _vDouble{},
    _vStr{}
{
}

OpenTracing::Tag::Tag(const std::string& key, const double& value) :
    _key{ key },
    _vType{ jaegertracing::thrift::TagType::DOUBLE },
    _vBool{},
    _vDouble{ value },
    _vStr{}
{
}

OpenTracing::Tag::Tag(const std::string& key, const std::string& value) :
    _key{ key },
    _vType{ jaegertracing::thrift::TagType::STRING },
    _vBool{},
    _vDouble{},
    _vStr{ value }
{
    {
        std::ostringstream ss;
        ss << "        Tag::Tag addr: " << this;
        Tracer::file_logger.PrintLine(ss.str(), true);
    }
}

OpenTracing::Tag::~Tag()
{
    {
        std::ostringstream ss;
        ss << "        ~Tag";
        Tracer::file_logger.PrintLine(ss.str(), true);
    }
}

OpenTracing::Tag::operator std::string() const {
    std::stringstream ss;
    switch (this->_vType) {
    case jaegertracing::thrift::TagType::STRING:
        ss << this->_vStr;
        break;
    case jaegertracing::thrift::TagType::DOUBLE:
        ss << this->_vDouble;
        break;
    case jaegertracing::thrift::TagType::BOOL:
        ss << this->_vBool;
        break;
    default:
        ss << "not supported tag type";
    }
    return ss.str();
}
