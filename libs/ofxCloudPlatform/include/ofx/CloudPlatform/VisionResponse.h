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


#include "ofx/HTTP/BaseResponse.h"
#include "ofx/CloudPlatform/VisionRequest.h"
#include "ofx/HTTP/BaseClient.h"


namespace ofx {
namespace CloudPlatform {


class VisionResponse: public HTTP::BufferedResponse<VisionRequest>
{
public:
    using BufferedResponse<VisionRequest>::BufferedResponse;

    /// \brief Destroy a VisionResponse.
    virtual ~VisionResponse();

    static const std::string FACE_ANNOTATIONS;
    static const std::string LANDMARK_ANNOTATIONS;
    static const std::string LOGO_ANNOTATIONS;
    static const std::string LABEL_ANNOTATIONS;
    static const std::string TEXT_ANNOTATIONS;
    static const std::string SAFE_SEARCH_ANNOTATIONS;
    static const std::string IMAGE_PROPERTIES_ANNOTATIONS;

protected:
    virtual void bufferStream(std::istream& responseStream) override;

private:

    friend class HTTP::BaseClient;

};



} } // namespace ofx::CloudPlatform
