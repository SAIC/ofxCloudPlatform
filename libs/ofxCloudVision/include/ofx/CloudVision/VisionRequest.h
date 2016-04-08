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


#pragma once


#include "ofx/HTTP/JSONRequest.h"
#include "ofx/CloudVision/VisionRequestItem.h"


namespace ofx {
namespace CloudVision {


/// \brief A Google Cloud Platform Vision request.
class VisionRequest: public HTTP::JSONRequest
{
public:
    /// \brief Creates a default Vision request.
    VisionRequest();

    /// \brief Creates a Vision request with a custom endpoint URI.
    ///
    /// This can be used for testing against other endpoints.
    ///
    /// \param uri The endpoint URI to use.
    VisionRequest(const std::string& uri);

    /// \brief Destroy the VisionRequest.
    virtual ~VisionRequest();

    /// \brief Add a request item.
    /// \param request The request item to add.
    void addRequestItem(const RequestItem& requestItem);

    /// \brief The default request URI.
    static const std::string DEFAULT_VISION_REQUEST_URI;

protected:
    /// \brief We hide this method for data integreity.
    void setJSON(const ofJson& json) override;

};



} } // namespace ofx::CloudVision
