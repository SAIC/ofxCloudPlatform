//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <string>
#include "ofConstants.h"
#include "ofx/HTTP/OAuth20RequestFilter.h"
#include "ofx/HTTP/PostRequest.h"


namespace ofx {
namespace CloudPlatform {


/// \brief Google Cloud Platform Service Accoutn Credentials.
/// \sa https://developers.google.com/identity/protocols/OAuth2ServiceAccount
class ServiceAccountCredentials
{
public:
    /// \brief Create an empty ServiceAccountCredentials.
    ServiceAccountCredentials();

    /// \brief Destroy the ServiceAccountCredentials.
    virtual ~ServiceAccountCredentials();

    /// \brief Set the project id.
    /// \param projectId the project id.
    void setProjectId(const std::string& projectId);

    /// \returns the project id.
    std::string getProjectId() const;

    /// \brief Set the private key id.
    /// \param privateKeyId The private key id.
    void setPrivateKeyId(const std::string& privateKeyId);

    /// \returns the private key id.
    std::string getPrivateKeyId() const;

    /// \brief The private key PEM.
    /// \param privateKey the private key PEM.
    void setPrivateKey(const std::string& privateKey);

    /// \returns the private key.
    std::string getPrivateKey() const;

    /// \brief Set the client email.
    /// \param clientEmail The client email.
    void setClientEmail(const std::string& clientEmail);

    /// \returns the client email.
    std::string getClientEmail() const;

    /// \brief Set the client id.
    /// \param clientId the client id.
    void setClientId(const std::string& clientId);

    /// \returns the client id.
    std::string getClientId() const;

    /// \brief Set the client X.509 certificate URL.
    /// \param clientX509CertURL The client certificate URL.
    void setClientX509CertURL(const std::string& url);

    /// \returns the client X.509 certificate URL.
    std::string getClientX509CertURL() const;

    /// \brief Set the authorization URI.
    /// \param uri The authorization URI.
    void setAuthURI(const std::string& uri);

    /// \returns the authorization URI.
    std::string getAuthURI() const;

    /// \brief Set the authorization provider X.509 certificate URL.
    /// \param authProviderX509CertURL The authorization certificate URL.
    void setAuthProviderX509CertURL(const std::string& url);

    /// \returns the authorization provider X.509 certificate URL.
    void getAuthProviderX509CertURL(const std::string& url);

    /// \brief Set the token URI.
    /// \param uri The token URI.
    void setTokenURI(const std::string& uri);

    /// \returns the token URI.
    std::string getTokenURI() const;

    /// \brief Load account credentials from json.
    /// \param json The json to parse.
    /// \returns the ServiceAccountCredentials.
    static ServiceAccountCredentials fromJSON(const ofJson& json);

    /// \brief Load account credentials from json on disk.
    /// \param credentialsPath the absolute file path of the credentials.
    /// \returns the ServiceAccountCredentials.
    static ServiceAccountCredentials fromFile(const std::string credentialsPath);

private:
    /// \brief The project id.
    std::string _projectId;

    /// \brief The private key id.
    std::string _privateKeyId;

    /// \brief The private key PEM.
    std::string _privateKey;

    /// \brief The client email.
    std::string _clientEmail;

    /// \brief The client id.
    std::string _clientId;

    /// \brief The client X.509 certificate URL.
    std::string _clientX509CertURL;

    /// \brief Set the authorization URI.
    std::string _authURI;

    /// \brief The authorization provider X.509 certificate URL.
    std::string _authProviderX509CertURL;

    /// \brief The token URI.
    std::string _tokenURI;

};


/// \brief Construct a Google Cloud Platform Service Account Token Request.
class ServiceAccountTokenRequest: public HTTP::PostRequest
{
public:
    /// \brief Create a default ServiceAccountTokenRequest.
    /// \param credentials The Google ServiceAccountCredentials.
    /// \param scope The scope of the token request.
    ServiceAccountTokenRequest(const ServiceAccountCredentials& credentials,
                               const std::string& scope = DEFAULT_SCOPE);

    /// \brief Destroy the ServiceAccountTokenRequest.
    virtual ~ServiceAccountTokenRequest();

    /// \brief The default scope for Google Cloud Platform requests.
    /// \sa https://www.googleapis.com/auth/cloud-platform
    static const std::string DEFAULT_SCOPE;

};


/// \brief A OAuth2.0 service account response to a token request.
class ServiceAccountToken
{
public:
    /// \brief Create an empty ServiceAccountToken.
    ServiceAccountToken();

    /// \brief Create a ServiceAccountToken with the given parameters.
    /// \param The token Type
    ServiceAccountToken(const std::string& tokenType,
                        const std::string& accessToken,
                        uint64_t expiresIn);

    virtual ~ServiceAccountToken();

    std::string accessToken() const;

    std::string tokenType() const;

    uint64_t expiresIn() const;

    uint64_t issuedTime() const;

    bool isExpired() const;

    static ServiceAccountToken fromJSON(const ofJson& json);

private:
    std::string _tokenType;
    std::string _accessToken;
    uint64_t _expiresIn = 0;
    uint64_t _issuedTime = 0;

};


/// \brief A filter responsible for managing Google Platform authentication.
///
/// This class is thread-safe, making it possible for a single PlatformClient
/// to be used in a multi-threaded environment.
class ServiceAccountTokenFilter: public HTTP::AbstractRequestFilter
{
public:
    ServiceAccountTokenFilter();
    
    ServiceAccountTokenFilter(const ServiceAccountCredentials& credentials);

    virtual ~ServiceAccountTokenFilter();

    void requestFilter(HTTP::BaseRequest& request,
                       HTTP::Context& context) override;

    void setCredentials(const ServiceAccountCredentials& credentials);

    const ServiceAccountCredentials& getCredentials() const;

    void setToken(const ServiceAccountToken& token);

    const ServiceAccountToken& getToken() const;

private:
    ServiceAccountCredentials _credentials;

    ServiceAccountToken _token;

    mutable std::mutex _mutex;

};


} } // namespace ofx::CloudPlatform
