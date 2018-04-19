//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/CloudPlatform/PlatformClient.h"


namespace ofx {
namespace CloudPlatform {


PlatformClient::PlatformClient(): PlatformClient(ServiceAccountCredentials())
{
}


PlatformClient::PlatformClient(const ServiceAccountCredentials& credentials)
{
    setCredentials(credentials);
    addRequestFilter(&_serviceAccountTokenFilter);
}


PlatformClient::~PlatformClient()
{
}


void PlatformClient::setCredentials(const ServiceAccountCredentials& credentials)
{
    _serviceAccountTokenFilter.setCredentials(credentials);
}


const ServiceAccountCredentials& PlatformClient::getCredentials() const
{
    return _serviceAccountTokenFilter.getCredentials();
}


} } // namespace ofx::CloudPlatform
