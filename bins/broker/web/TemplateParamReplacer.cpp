/*
 * Copyright 2014-present IVK JSC. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Poco/File.h>
#include <Poco/FileStream.h>
#include <Poco/Path.h>
#include <cctype>
#include "TemplateParamReplacer.h"
#include "Defines.h"
#include "Configuration.h"

TemplateParamReplacer::TemplateParamReplacer(std::string pageName) : _pageName(std::move(pageName)) {}

TemplateParamReplacer::~TemplateParamReplacer() = default;

void TemplateParamReplacer::addReplacer(const std::string &param, TemplateParamReplacer::Callback callback) {
  _handlerMap.insert(make_pair(param, callback));
}

std::string TemplateParamReplacer::operator[](const std::string &param) { return (this->*_handlerMap[param])(); }

std::string TemplateParamReplacer::loadTemplate(const std::string &fileName) {
  std::string result;
  Poco::Path wwwPath;
  wwwPath.assign(CONFIGURATION::Instance().http().site).makeDirectory().append(fileName).makeFile();

  Poco::File f(wwwPath.toString());
  if (f.exists()) {
    Poco::FileInputStream fileIS(wwwPath.toString(), std::ios::binary);
    auto sz = f.getSize();
    std::vector<char> data;
    data.resize(static_cast<size_t>(sz) + 1);
    fileIS.read(&data[0], static_cast<std::streamsize>(sz));
    result.assign(&data[0], static_cast<size_t>(sz));
  }
  return result;
}

std::string TemplateParamReplacer::replace() {
  std::string htmlTemplate = loadTemplate(_pageName);
  if (!htmlTemplate.empty()) {
    for (auto &it : _handlerMap) {
      replaceStringInPlace(htmlTemplate, (it.first), (this->*it.second)());
    }
  }
  return htmlTemplate;
}

void TemplateParamReplacer::replaceStringInPlace(std::string &subject, const std::string &search, const std::string &replace) {
  size_t position = 0;

  auto getFirstBrace = [&subject](size_t pos) {
    while (pos > 0) {
      --pos;
      if (subject[pos] == '{') {
        return pos;
      }
    }
    return pos;
  };
  auto getLastBrace = [&subject](size_t pos) {
    while (pos < subject.length()) {
      ++pos;
      if (subject[pos] == '}') {
        return pos;
      }
    }
    return pos;
  };

  while ((position = subject.find(search, position)) != std::string::npos) {
    if (std::isalpha(subject[position + search.length()])) {
      position += search.length();
      continue;
    }
    size_t firstBracePosition = getFirstBrace(position);
    if (firstBracePosition > 0) {
      size_t lastBracePosition = getLastBrace(position);
      if (lastBracePosition < subject.length()) {
        size_t length = lastBracePosition - firstBracePosition + 1;
        subject.replace(firstBracePosition, length, replace);
        position = lastBracePosition;
      }
    } else {
      ++position;
    }
  }
}

std::string TemplateParamReplacer::getH1() const { return _pageName; }
