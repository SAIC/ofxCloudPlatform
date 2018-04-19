//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofx/HTTP/Client.h"
#include "ofx/HTTP/Response.h"
#include "ofx/CloudPlatform/ServiceAccount.h"


namespace ofx {
namespace CloudPlatform {


class PlatformClient: public HTTP::Client
{
public:
    PlatformClient();
    PlatformClient(const ServiceAccountCredentials& credentials);

    virtual ~PlatformClient();

    void setCredentials(const ServiceAccountCredentials& credentials);

    const ServiceAccountCredentials& getCredentials() const;

private:
    virtual void requestFilter(HTTP::Context& context,
                               HTTP::Request& request) const override;
    
    ServiceAccountTokenFilter _serviceAccountTokenFilter;

};


} } // namespace ofx::CloudPlatform
