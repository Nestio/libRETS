/*
 * Copyright (C) 2005 National Association of REALTORS(R)
 *
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished
 * to do so, provided that the above copyright notice(s) and this
 * permission notice appear in all copies of the Software and that
 * both the above copyright notice(s) and this permission notice
 * appear in supporting documentation.
 */
#include <sstream>
#include <boost/lexical_cast.hpp>                                               
#include "librets/RetsHttpRequest.h"
#include "librets/util.h"

using namespace librets;
using namespace librets::util;
using std::string;
using std::ostringstream;
using boost::lexical_cast; 

RetsHttpRequest::RetsHttpRequest()
    : mQueryParameters(), mQueryParametersChanged(false), mLogging(true)
{
    mMethod = GET;
}

RetsHttpRequest::~RetsHttpRequest()
{
}

void RetsHttpRequest::SetUrl(string url)
{
    mUrl = url;
}

string RetsHttpRequest::GetUrl() const
{
    return mUrl;
}

void RetsHttpRequest::SetMethod(Method method)
{
    mMethod = method;
}

RetsHttpRequest::Method RetsHttpRequest::GetMethod() const
{
    return mMethod;
}

void RetsHttpRequest::SetHeader(string name, string value)
{
    mHeaders[name] = value;
}

void RetsHttpRequest::ClearHeader(string name)
{
    mHeaders.erase(name);
}

StringMap RetsHttpRequest::GetHeaderMap() const
{
    return mHeaders;
}

void RetsHttpRequest::SetQueryParameter(string name, int value)
{
    SetQueryParameter(name, lexical_cast<string>(value));
}

void RetsHttpRequest::SetQueryParameter(string name, string value)
{
    if (!value.empty())
    {
        mQueryParameters[name] = urlEncode(value);
    }
    else
    {
        mQueryParameters.erase(name);
    }
    mQueryParametersChanged = true;
}

void RetsHttpRequest::GenerateQueryString() const
{
    if (!mQueryParametersChanged)
        return;
    
    ostringstream queryString;
    string separator = "";
    StringMap::const_iterator i;
    for (i = mQueryParameters.begin(); i != mQueryParameters.end(); i++)
    {
        const string & name = i->first;
        const string & value = i-> second;
        queryString << separator << name << "=" << value;
        separator = "&";
    }
    mQueryString = queryString.str();
    mQueryParametersChanged = false;
}

std::string RetsHttpRequest::GetQueryString() const
{
    GenerateQueryString();
    return mQueryString;
}

bool RetsHttpRequest::GetLogging()
{
    return mLogging;
}

void RetsHttpRequest::SetNoLogging()
{
    mLogging = false;
}

void RetsHttpRequest::SetLogging()
{
    mLogging = true;
}
