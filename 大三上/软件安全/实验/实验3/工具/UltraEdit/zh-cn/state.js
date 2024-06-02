


//get data from softAnchor
var message = "";
var state 	= window.external.MyState;
var seconds = window.external.MySeconds;
var days 	= window.external.MyDays;
var runs 	= window.external.MyRuns;
var purchaseUrl = window.external.PurchaseUrl;
var supportUrl = window.external.SupportUrl;
var productName = window.external.AppProductName;
var buttonState = window.external.ButtonState;
var licenseKey = window.external.MyLicenseKey;
var productExId = window.external.MyProductExId;
var myDomain = window.external.MyDomain;



//possible state values
var eLicenseSubscription = -50;
var eLicenseTrial = 	-51;
var eLicenseGrace = -52;
var eLicenseExpired = -53;
var eLicenseInfinite = -54;
var eLicenseTimeBombRunning = -56;
var eLicenseNotInitialized = -6;
var eLicenseInvalidSignature = -15;
var eLicenseInvalidSignature2 = -1158;


function setState()
{
	setIcon();	
	setStartPosition();
	setButtonState();
	setUrls();
	setMessageState();
	setProductName();
}

function setIcon()
{
	//window.external.FormIcon = "favicon.ico";
}

function setStartPosition()
{
	window.external.FormStartPosition = 1; //centerscreen;
}


function setButtonState()
{
	//button state values
	if (state == eLicenseExpired || state == eLicenseNotInitialized || buttonState == 1)
	{		
		//$("#btnPlayTrial img").attr("src", "but_close.png");
		//$("#btnPlayTrial a").attr("href", "sa://close");
		$("#continueTrial a").attr("href", "sa://close");
		$("#continueTrial span").attr("innerHTML", '&nbsp;'+STATE_closeLabel+'&nbsp;');
	}
}

function setProductName()
{
	$("#productName").attr("innerHTML",productName+" ");
	$("#productName1").attr("innerHTML",productName);
	$("#productName2").attr("innerHTML",productName);
}

function setUrls()
{

	$("a.purchaseUrl").attr("href", purchaseUrl);
	$("a#purchaseUrl").attr("href", purchaseUrl);
	$("a.purchaseUrl2").attr("href", purchaseUrl);
	$("a#purchaseUrl2").attr("href", purchaseUrl);
	$("a.supportUrl").attr("href", supportUrl);
	$("a.boldOrange").attr("href", purchaseUrl);			
	$("a.offlineTarget").attr("href", makeOfflineTarget());
	
}

function makeOfflineTarget()
{
	return myDomain + "/amsweb/offlineact/offlineActivation.jsf?pid=" + productExId;
}

function makeDeactivationTarget()
{
	return myDomain + "/amsweb/deact/deactivation.jsf?pid=" + productExId;
}


function setMessageState()
{

	if(state == eLicenseInvalidSignature || state == eLicenseInvalidSignature2)
	{
		          // 'Your license file appears to be corrupted.'
		message = STATE_msgInvalidSignature;
	}

	
	if (state == eLicenseExpired || state == eLicenseNotInitialized)
	{
		           // 'Your free trial is over.'
		message = STATE_msgExpired;
	}

	if (state == eLicenseInfinite)
	{
		message == "";
	}

	if (state == eLicenseGrace)
	{
		           // 'Something is wrong with your license. The application has entered a grace period. '
		message += STATE_msgGrace;
		state = eLicenseTrial; //flip to trial to show times.
	}

	if (state == eLicenseTrial || state == eLicenseTimeBombRunning || state == eLicenseSubscription)
	{

		if (runs == 0 && days == 0)
		{

			if (seconds >=3600)
			{
				var hours = Math.round(seconds/3600);

				if (hours == 1)
				{
					           // 'You currently have 1 hour remaining.'
					message += STATE_msg1Hr;
				}
				else
				{
					           // 'You currently have'                      // 'hours remaining.'
					message += STATE_msgCurrentlyHave + " " + hours + " " + STATE_msgHrsRemaining;
				}
			}
			else if (seconds >= 60)
			{

				var minutes = Math.round(seconds/60);

				if (minutes == 1)
				{
                      // 'You currently have 1 minute remaining.'
					message += STATE_msg1Min;
				}
				else
				{
                     // 'You currently have'                        // 'minutes remaining.'
					message += STATE_msgCurrentlyHave + " " + minutes + " " + STATE_msgMinsRemaining;
				}

			}
			else
			{
				           // 'You currently have'                        // 'seconds remaning'
				message += STATE_msgCurrentlyHave + " " + seconds + " " + STATE_msgSecsRemaining;
			}
		}	
		else if (days == 0 && seconds==0 && runs != 0)
		{
			           // 'You currently have'                     // 'runs remaining.'
			message += STATE_msgCurrentlyHave + " " + runs + " " + STATE_msgRunsRemaining;
		}
		else if (days != 0 && runs != 0)
		{
			           // 'You currently have'               // 'days or'                         // 'runs remaining.'
			message += STATE_msgCurrentlyHave + days + " " + STATE_msgDaysOr + " " + runs + " " + STATE_msgRunsRemaining;
		}
		else if (days != 0 && runs == 0)
		{
			           // 'You currently have'                     // 'days remaining'.
			message += STATE_msgCurrentlyHave + " " + days + " " + STATE_msgDaysRemaining;
		}
		else if (days==0 && seconds!=0 && runs!=0)
		{
			var firstHalf = "";
			if (seconds >=3600)
			{
				var hours = Math.round(seconds/3600);

				if (hours == 1)
				{
					             // "You currently have 1 hour"
					firstHalf += STATE_msg1Hr_2;
				}
				else if(hours>1)
				{
					             // "You currently have "                     // 'hours'
					firstHalf += STATE_msgCurrentlyHave + " " + hours + " " + STATE_msgHrLabel;
				}
				
				
			}
			else if (seconds >= 60)
			{

				var minutes = Math.round(seconds/60);

				if (minutes == 1)
				{
					// "You currently have 1 minute"					
					firstHalf += STATE_msg1Min_2;
				}
				else
				{
                       // "You currently have 1 minute"					       //" minutes"
					firstHalf += STATE_msgCurrentlyHave + " "  + minutes + " " + STATE_msgMinLabel;
				}

			}
			else
			{
				           // "You currently have 1 minute"	              // 'seconds'
				message += STATE_msgCurrentlyHave + " " + seconds + " " + STATE_msgSecondsLabel;
			}
			
			var secondHalf = "";
			
			if (runs==1)
			{
				             // 'or 1 run remaining.'
				secondHalf += STATE_msg1RunRemaining;
			}
			else
			{
				              // 'or'                               // " runs remaining."
				secondHalf += STATE_msgOrLabel + " " + runs + " " + STATE_msgRunsRemaining_2;
			}
			
			message+=firstHalf+" " + secondHalf;
			
		}
		
	}

	$("#ptrialMessage").html(message);
}