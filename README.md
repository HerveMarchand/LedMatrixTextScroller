# LedMatrixTextScroller
This Arduino Library allows to display a text using scroll mode on 8x8 Led Matrix - MAX7219 

API Description
1) MatrixTextScrollerClass : To instanciate the service providing connected PIN (CLK, CS and DIN)

2) setTextToDisplay : To provide the text to display. In this case the text will be displayed continously.

3) setTextToDisplayWithLoopNumber : To provide the text to display. In this case the text will be displayed continously. In this case the number of loop (scroll text) can be provided.

4) setIntensity : To tune the Led Matrix intensity [0..15] (0 for low intensity, 15 for high intensity)

5) cleanMatrix : To clean the Led Matrix

6) setTextUpdatePeriod : To tune the text scrolling speed (defaut is 30). 

7) startDisplay / stopDisplay : To start / stop text scrolling

8) getDisplayStatus : To retrieve the text scrolling status (false is Not active / true is active)

9) refresh : Call this method from the main loop in order to refresh the Led Matrix
