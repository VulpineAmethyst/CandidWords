/*
 * Copyright 2022 Síle Ekaterin Liszka
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <cctype>

#include "words.hh"

void usage(char *);

std::vector<std::string> green_search(std::string invalid, std::string yellow, std::string green) {
    std::vector<std::string> candidates;

    for (std::vector<std::string>::size_type i = 0; i < wordv.size(); i++) {
        bool valid = false;
        std::string word(wordv[i]);

        for (int j = 0; j < 5; j++) {
            if (invalid.find(word[j]) != std::string::npos) {
                valid = false;
                break;
            }
            if (green[j] == '?') {
                continue;
            }
            if (word[j] == green[j]) {
                valid = true;
            }
            else {
                valid = false;
                break;
            }
        }
        for (std::string::size_type j = 0; j < yellow.length(); j++) {
            if (word.find(yellow[j]) == std::string::npos) {
                valid = false;
                break;
            }
        }
        if (valid) {
            candidates.push_back(word);
        }
    }
    return candidates;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        usage(argv[0]);
        return -1;
    }
    std::string yellow(argv[1]);
    std::string green(argv[2]);
    std::string guessed(argv[3]);
    std::string invalid;
    std::vector<std::string> candidates;

    // Are these arguments acceptable?
    for (std::string::size_type i = 0; i < yellow.length(); i++) {
        if (!std::isalpha(yellow[i])){
            std::cerr << "invalid yellow " << yellow[i] << " at " << i << std::endl;
            usage(argv[0]);
            return -1;
        }
    }
    for (std::string::size_type i = 0; i < green.length(); i++) {
        if (!std::isalpha(green[i]) && (green[i] != '?')) {
            std::cerr << "invalid green at" << green[i] << " at " << i << std::endl;
            usage(argv[0]);
            return -1;
        }
    }
    for (std::string::size_type i = 0; i < guessed.length(); i++) {
        if (!std::isalpha(guessed[i])) {
            std::cerr << "invalid guessed " << yellow[i] << " at " << i << std::endl;
            usage(argv[0]);
            return -1;
        }
    }

    // What letters aren't valid?
    for (std::string::size_type i = 0; i < guessed.length(); i++) {
        if (yellow.find(guessed[i]) == std::string::npos) {
            invalid.append(1, guessed[i]);
        }
    }
    if (green != "?????") {
        candidates = green_search(invalid, yellow, green);
    }

    std::for_each(candidates.begin(), candidates.end(), [](std::string n) { std::cout << n << " "; });
    std::cout << std::endl;
}

void usage(char *progname) {
    std::cerr << "Usage: " << progname << " <yellow> <green> <guessed>\n\n" <<
        "<yellow> must be up to five letters which are contained in the word.\n" <<
        "<green> must be either question marks or correctly-placed letters.\n" <<
        "<guessed> is all of the letters guessed so far.\n";
}
