##ofxDatGuiUC

**ofxDatGuiUC** is an Unicode compatible version of [**ofxDatGUI**](https://braitsch.github.io/ofxDatGui/).

The original version of `ofxDatGUI` does not support multi-bytes characters, because it depends on `ofxTrueTypeFont`, which does not support either. Thanks to `ofxTrueTypeFontUC`, this version successfully support multi-bytes unicode characters.

All header files are the same as the original one, so if you already uses it, you just need to create and set the custom theme to use a font file to support characters you want to use.

### Example
`
class ofxDatGuiThemeCustom : public ofxDatGuiTheme{
public:
    ofxDatGuiThemeVrtrip()
    {
        font.file = "anotherttf.ttf";
        init();
    }
};
`

`
void ofApp::setup()
{
    theme = new ofxDatGuiThemeCustom();
    yourcomponent->setTheme(theme);
}
`

