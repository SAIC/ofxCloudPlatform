//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/CloudPlatform/VisionDeserializer.h"


namespace ofx {
namespace CloudPlatform {


bool VisionDeserializer::fromJSON(const ofJson& json, ofPolyline& polyline)
{
    polyline.clear();
    for (const auto& vertex: json["vertices"])
    {
        glm::vec3 _vertex;
        fromJSON(vertex, _vertex);
        polyline.addVertex(_vertex);
    }
    return true;
}


bool VisionDeserializer::fromJSON(const ofJson& json, glm::vec3& position)
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
