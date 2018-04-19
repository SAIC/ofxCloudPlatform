//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofx/HTTP/HTTPClient.h"
#include "ofx/HTTP/BaseResponse.h"
#include "ofx/CloudPlatform/ServiceAccount.h"


namespace ofx {
namespace CloudPlatform {


class PlatformClient: public HTTP::HTTPClient
{
public:
    PlatformClient();
    PlatformClient(const ServiceAccountCredentials& credentials);

    virtual ~PlatformClient();

    void setCredentials(const ServiceAccountCredentials& credentials);

    const ServiceAccountCredentials& getCredentials() const;

private:
    ServiceAccountTokenFilter _serviceAccountTokenFilter;

};


} } // namespace ofx::CloudPlatform
