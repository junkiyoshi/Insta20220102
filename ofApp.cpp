#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);

	this->font_size = 20;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	this->font.load(font_settings);

	this->words = {

		"H", "A", "P", "P", "Y", 
		"N", "E", "W",
		"Y", "E", "A", "R"
	};

	for (int x = this->font_size * -15; x <= this->font_size * 15; x += this->font_size * 0.8) {

		for (int y = this->font_size * -15; y <= this->font_size * 15; y += this->font_size * 1.2) {

			this->location_list.push_back(glm::vec2(x - this->font_size * 0.2, y - this->font_size * 0.5));
			this->index_list.push_back(ofRandom(this->words.size()));
			this->param_list.push_back(true);
		}
	}


}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 15 == 0) {

		auto l = glm::vec2(ofRandom(-250, 250), ofRandom(-250, 250));
		auto f = 5;
		this->wave_list.push_back(make_pair(l, f));
	}

	for (auto& param : this->param_list) {

		param = false;
	}

	auto max_height = 150;
	for (auto& wave : this->wave_list) {

		for (int i = 0; i < this->location_list.size(); i++) {

			auto distance = glm::distance(wave.first, this->location_list[i]);
			if (distance > wave.second - this->font_size * 1.2 && distance < wave.second + this->font_size * 1.2) {

				this->index_list[i] = (this->index_list[i] + 1) % this->words.size();
				this->param_list[i] = true;
			}
		}
		
		wave.second += 12;
	}

	for (int i = this->wave_list.size() - 1; i >= 0; i--) {

		if (this->wave_list[i].second > 650) {

			this->wave_list.erase(this->wave_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int i = 0; i < this->location_list.size(); i++) {

		if (this->param_list[i]) {

			ofSetColor(0);
		}
		else {

			ofSetColor(128);
		}

		this->font.drawString(this->words[this->index_list[i]], this->location_list[i].x, this->location_list[i].y);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}