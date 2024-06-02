
function setFrameSize(width, height)
{
	if (width < 400) {
		width = 400;
	}
	if (height < 200) {
		height = 200;
	}
	window.external.AppHeight = height;	
	window.external.AppWidth = width;
}


