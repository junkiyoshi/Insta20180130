#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(255);
	ofSetWindowTitle("Insta");

	ofSetColor(0, 32, 255);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 250, true, false, true);
	this->words = "OTHER";
	this->words_size = ofPoint(this->font.stringWidth(this->words), this->font.stringHeight(this->words));
	this->paths = this->font.getStringAsPoints(this->words);
}

//--------------------------------------------------------------
void ofApp::update() {
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	for (int p_index = 0; p_index < this->paths.size(); p_index++) {

		vector<ofPolyline> outline = this->paths[p_index].getOutline();
		
		for (int o_index = 0; o_index < outline.size(); o_index++) {

			outline[o_index] = outline[o_index].getResampledBySpacing(30);
			ofMesh mesh;
			ofTessellator t;
			t.tessellateToMesh(outline, ofPolyWindingMode::OF_POLY_WINDING_ODD, mesh);

			vector<ofMeshFace> triangles = mesh.getUniqueFaces();
			for (int i = 0; i < triangles.size(); i++) {

				ofPoint avg = (triangles[i].getVertex(0) + triangles[i].getVertex(1) + triangles[i].getVertex(2)) / 3;
				float noise_value = ofNoise(avg.x * 0.005 - ofGetFrameNum() * 0.05);

				ofMesh draw_mesh;
				ofPoint adjust(-this->words_size.x / 2, this->words_size.y / 2);

				if (noise_value < 0.4){

					adjust += ofPoint(0, 0, 500 * (noise_value - 0.4));
				}
				
				draw_mesh.addVertex(triangles[i].getVertex(0) + adjust);
				draw_mesh.addVertex(triangles[i].getVertex(1) + adjust);
				draw_mesh.addVertex(triangles[i].getVertex(2) + adjust);

				draw_mesh.draw();
			}
			
		}
	}

	this->cam.end();
}

//========================================================================
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}