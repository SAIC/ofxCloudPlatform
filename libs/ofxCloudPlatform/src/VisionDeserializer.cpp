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


#include "ofx/CloudPlatform/VisionDeserializer.h"


namespace ofx {
namespace CloudPlatform {


bool VisionDeserializer::fromJSON(const ofJson& json, ofPolyline& polyline)
{
    polyline.clear();
    for (const auto& vertex: json["vertices"])
    {
        ofVec2f _vertex;
        fromJSON(vertex, _vertex);
        polyline.addVertex(_vertex);
    }
    return true;
}


bool VisionDeserializer::fromJSON(const ofJson& json, ofVec2f& position)
{
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();
        if (key == "x") position.x = value;
        else if (key == "y") position.y = value;
        else ofLogWarning() << "Unknown key " << key << " - " << json.dump(4);
        ++iter;
    }
    
    return true;
}



bool VisionDeserializer::fromJSON(const ofJson& json, ofVec3f& position)
{
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();
        if (key == "x") position.x = value;
        else if (key == "y") position.y = value;
        else if (key == "z") position.z = value;
        else ofLogWarning() << "Unknown key " << key << " - " << json.dump(4);
        ++iter;
    }

    return true;
}


bool VisionDeserializer::fromJSON(const ofJson& json, ofColor& color)
{
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();
        if (key == "red") color.r = value;
        else if (key == "green") color.g = value;
        else if (key == "blue") color.b = value;
        else if (key == "alpha") color.a = value;
        else ofLogWarning() << "Unknown key " << key << " - " << json.dump(4);
        ++iter;
    }
    
    return true;
}


} } // namespace ofx::CloudPlatform
