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


#include "ofx/HTTP/BaseClient.h"
#include "ofx/HTTP/BaseResponse.h"
#include "ofx/CloudPlatform/VisionAnnotations.h"
#include "ofx/CloudPlatform/VisionRequest.h"


namespace ofx {
namespace CloudPlatform {


class AnnotateImageResponse
{
public:
    AnnotateImageResponse();
    ~AnnotateImageResponse();

    const std::vector<FaceAnnotation>& faceAnnotations() const;
    const std::vector<EntityAnnotation>& landmarkAnnotations() const;
    const std::vector<EntityAnnotation>& logoAnnotations() const;
    const std::vector<EntityAnnotation>& labelAnnotations() const;
    const std::vector<EntityAnnotation>& textAnnotations() const;
    const SafeSearchAnnotation& safeSearchAnnotation() const;
    const ImagePropertiesAnnotation& imagePropertiesAnnotation() const;

    static AnnotateImageResponse fromJSON(const ofJson& json);

private:
    std::vector<FaceAnnotation> _faceAnnotations;
    std::vector<EntityAnnotation> _landmarkAnnotations;
    std::vector<EntityAnnotation> _logoAnnotations;
    std::vector<EntityAnnotation> _labelAnnotations;
    std::vector<EntityAnnotation> _textAnnotations;
    SafeSearchAnnotation _safeSearchAnnotation;
    ImagePropertiesAnnotation _imagePropertiesAnnotation;

};


class VisionResponse: public HTTP::BufferedResponse<VisionRequest>
{
public:
    using BufferedResponse<VisionRequest>::BufferedResponse;

    /// \brief Destroy a VisionResponse.
    virtual ~VisionResponse();

    std::vector<AnnotateImageResponse> responses() const;

    static std::vector<AnnotateImageResponse> fromJSON(const ofJson& json);

protected:
    virtual void bufferStream(std::istream& responseStream) override;

private:
    std::vector<AnnotateImageResponse> _responses;

    friend class HTTP::BaseClient;

};



} } // namespace ofx::CloudPlatform
