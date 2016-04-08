// =============================================================================
//
// Copyright (c) 2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofx/CloudPlatform/ServiceAccount.h"
#include "ofFileUtils.h"
#include "ofLog.h"
#include "ofUtils.h"
#include "ofx/HTTP/JSONWebToken.h"


namespace ofx {
namespace CloudPlatform {


ServiceAccountCredentials::ServiceAccountCredentials()
{
}


ServiceAccountCredentials::~ServiceAccountCredentials()
{
}


void ServiceAccountCredentials::setProjectId(const std::string& projectId)
{
    _projectId = projectId;
}


std::string ServiceAccountCredentials::getProjectId() const
{
    return _projectId;
}


void ServiceAccountCredentials::setPrivateKeyId(const std::string& privateKeyId)
{
    _privateKeyId = privateKeyId;
}


std::string ServiceAccountCredentials::getPrivateKeyId() const
{
    return _privateKeyId;
}


void ServiceAccountCredentials::setPrivateKey(const std::string& privateKey)
{
    _privateKey = privateKey;
}


std::string ServiceAccountCredentials::getPrivateKey() const
{
    return _privateKey;
}


void ServiceAccountCredentials::setClientEmail(const std::string& clientEmail)
{
    _clientEmail = clientEmail;
}


std::string ServiceAccountCredentials::getClientEmail() const
{
    return _clientEmail;
}


void ServiceAccountCredentials::setClientId(const std::string& clientId)
{
    _clientId = clientId;
}


std::string ServiceAccountCredentials::getClientId() const
{
    return _clientId;
}


void ServiceAccountCredentials::setClientX509CertURL(const std::string& url)
{
    _clientX509CertURL = url;
}


std::string ServiceAccountCredentials::getClientX509CertURL() const
{
    return _clientX509CertURL;
}


void ServiceAccountCredentials::setAuthURI(const std::string& uri)
{
    _authURI = uri;
}


std::string ServiceAccountCredentials::getAuthURI() const
{
    return _authURI;
}


void ServiceAccountCredentials::setTokenURI(const std::string& uri)
{
    _tokenURI = uri;
}


std::string ServiceAccountCredentials::getTokenURI() const
{
    return _tokenURI;
}


void ServiceAccountCredentials::setAuthProviderX509CertURL(const std::string& url)
{
    _authProviderX509CertURL = url;
}


void ServiceAccountCredentials::getAuthProviderX509CertURL(const std::string& url)
{
    return _authProviderX509CertURL;
}


ServiceAccountCredentials ServiceAccountCredentials::fromJSON(const ofJson& json)
{
    if (json["type"].is_null() || (json["type"].is_string() && json["type"].get<std::string>().compare("service_account") != 0))
    {
        ofLogError("ServiceAccountCredentials::fromJSON") << "Invalid credentials file.";
        return ServiceAccountCredentials();
    }

    ServiceAccountCredentials credentials;

    if (json["project_id"].is_string())
    {
        credentials.setProjectId(json["project_id"]);
    }

    if (json["private_key_id"].is_string())
    {
        credentials.setPrivateKeyId(json["private_key_id"]);
    }

    if (json["private_key"].is_string())
    {
        credentials.setPrivateKey(json["private_key"]);
    }

    if (json["client_email"].is_string())
    {
        credentials.setClientEmail(json["client_email"]);
    }

    if (json["client_id"].is_string())
    {
        credentials.setClientId(json["client_id"]);
    }

    if (json["auth_uri"].is_string())
    {
        credentials.setAuthURI(json["auth_uri"]);
    }

    if (json["token_uri"].is_string())
    {
        credentials.setTokenURI(json["token_uri"]);
    }

    if (json["auth_provider_x509_cert_url"].is_string())
    {
        credentials.setProjectId(json["auth_provider_x509_cert_url"]);
    }

    if (json["client_x509_cert_url"].is_string())
    {
        credentials.setProjectId(json["client_x509_cert_url"]);
    }

    return credentials;
}


ServiceAccountCredentials ServiceAccountCredentials::fromFile(const std::string credentialsPath)
{
    ofFile file(ofToDataPath(credentialsPath, true));

    if (file.exists())
    {
        std::string extension = file.getExtension();

        if (extension.compare("json") == 0)
        {
            ofJson json;
            file >> json;
            return fromJSON(json);
        }
        else
        {
            ofLogError("ServiceAccountCredentials::fromJSON") << "Expected .json file. " << file.path();
            return ServiceAccountCredentials();
        }
    }
    else
    {
        ofLogError("ServiceAccountCredentials::fromJSON") << "Unable to load " << file.path();
        return ServiceAccountCredentials();
    }
}


const std::string ServiceAccountTokenRequest::DEFAULT_SCOPE = "https://www.googleapis.com/auth/cloud-platform";


ServiceAccountTokenRequest::ServiceAccountTokenRequest(const ServiceAccountCredentials& credentials,
                                                       const std::string& scope):
    HTTP::PostRequest(credentials.getTokenURI(), Poco::Net::HTTPMessage::HTTP_1_1)
{
    HTTP::JSONWebSignatureHeader header;
    header.setType("JWT");
    header.setAlgorithm(HTTP::JSONWebSignatureHeader::Algorithm::RS256);
    header.setKeyId(credentials.getPrivateKey());

    uint64_t issuedAt = ofGetUnixTime();

    HTTP::JSONWebTokenPayload payload;
    payload.setIssuer(credentials.getClientEmail());
    payload.setIssuedAtTime(issuedAt);
    payload.setExpirationTime(issuedAt + 3600);
    payload.setAudience(credentials.getTokenURI());
    payload.set("scope", scope);

    std::string token = ofx::HTTP::JSONWebToken::generateToken(credentials.getPrivateKey(),
                                                               "notasecret",
                                                               header,
                                                               payload);

    addFormField("grant_type", "urn:ietf:params:oauth:grant-type:jwt-bearer");
    addFormField("assertion", token);
}


ServiceAccountTokenRequest::~ServiceAccountTokenRequest()
{
}


ServiceAccountToken::ServiceAccountToken()
{
}


ServiceAccountToken::ServiceAccountToken(const std::string& tokenType,
                                         const std::string& accessToken,
                                         uint64_t expiresIn):
    _tokenType(tokenType),
    _accessToken(accessToken),
    _expiresIn(expiresIn),
    _issuedTime(ofGetUnixTime())
{
}


ServiceAccountToken::~ServiceAccountToken()
{
}

std::string ServiceAccountToken::accessToken() const
{
    return _accessToken;
}


std::string ServiceAccountToken::tokenType() const
{
    return _tokenType;
}


uint64_t ServiceAccountToken::expiresIn() const
{
    return _expiresIn;
}


uint64_t ServiceAccountToken::issuedTime() const
{
    return _issuedTime;
}
    

bool ServiceAccountToken::isExpired() const
{
    return (ofGetUnixTime() - issuedTime()) > expiresIn();
}


ServiceAccountToken ServiceAccountToken::fromJSON(const ofJson& json)
{
    auto _accessToken = json.find("access_token");
    auto _tokenType = json.find("token_type");
    auto _expiresIn = json.find("expires_in");

    if (_accessToken != json.end() && _tokenType != json.end() && _expiresIn != json.end() &&
        _accessToken->is_string() && _tokenType->is_string() && _expiresIn->is_number())
    {
        return ServiceAccountToken(*_tokenType, *_accessToken, *_expiresIn);
    }
    else
    {
        auto _error = json.find("error");
        auto _errorDescription = json.find("error_description");

        std::string error = (_error != json.end()) ? *_error : "Unknown error.";
        std::string errorDescription = (_errorDescription != json.end()) ? *_errorDescription : "Unknown reason.";

        ofLogError("ServiceAccountToken::fromJSON") << "Error creating Token: " << error << ". " << errorDescription;
        return ServiceAccountToken();
    }

}

    
} } // namespace ofx::CloudPlatform
