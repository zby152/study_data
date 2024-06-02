
/*******************************************************
*  ERRORS.JS
*  N -> - (negative)
*  P -> + (positive)
*******************************************************/

var ERRORS_LabelErrorCode =
'Error code';

var ERRORS_n1000 = //kSAAuthorizeInvalidProductID
'It appears the product you are attempting to activate is invalid.';

var ERRORS_n1001 = //kSAAuthorizeMissingProductID
'It appears the product you are attempting to activate is invalid.';

var ERRORS_n1002 = //kSAAuthorizeInvalidFingerprint
'It appears the license key you are attempting to activate is not valid for this product.';

var ERRORS_n1003 = //kSAAuthorizeInvalidLicenseKey
"It appears the license key you are attempting to activate is not recognized. Please check the license key and try again.";

var ERRORS_n1004 =  //kSAAuthorizeOverLicenseDenial
'It appears this license key is over its installation limit. The key is currently active on too many systems.';

var ERRORS_n1005 =  //kSAAuthorizeOverLicenseWarning
'It appears this license key is very close to the installation limitt. You will only be able to install this key on one additional system. ';

var ERRORS_n1006 =  //kSAAuthorizeSuccess
'Success! Thank you.';

var ERRORS_n1007 =  //kSAAuthorizeFatalError
'It appears the activation servers are currently offline or experiencing difficulty. Please try to activate again later.';

var ERRORS_n1008 =  //kSAAuthorizeReactivation
'Success! Thank you.';

var ERRORS_n1009 =  //kSAAuthorizeUpgradeOnly
'You many not use this key to activate this product. This key is for upgrades only.';

var ERRORS_n1010 =  //kSAAuthorizeSubscriptionExpired
'It appears the subscription associated with this license key has expired.';

var ERRORS_n1011 =  //kSAAuthorizeTrialExpired
'It appears the trial for this license key has expired.';

var ERRORS_n1012 =  //kSAAuthorizeFeatureSubscriptionExpired
'';

var ERRORS_n1013 =  //kSAAuthorizeFeatureTrialExpired
'';

var ERRORS_n1014 =  //kSAAuthorizeFeatureTrialElapsed
'';

var ERRORS_n1015 =  //kSAAuthorizeInvalidUpgradeLicenseKey
'';

var ERRORS_n1016 =  //kSAAuthorizeActivationOnly
'';

var ERRORS_n1017 =  //kSAAuthorizeInvalidUpgradeOptionTrial
'';

var ERRORS_n1018 =  //kSAAuthorizeInvalidUpgradeOptionSubscription
'';

var ERRORS_n1019 =  //kSAAuthorizeBaseLicenseDeactivated
'';

var ERRORS_n1020 =  //kSAAuthorizeBaseLicenseNotActivated
'';

var ERRORS_n1021 =  //kSAAuthorizeUpgradeProductMismatch
'';

var ERRORS_n1022 =  //kSAAuthorizeDeactivationNotValidActionForLicense
'The license you have attempted to deactivate does NOT allow deactivation.';

var ERRORS_n1023 =  //kSAAuthorizeLicenseNotActivatedForDevice
'The license you have attempted to deactivate is NOT currently active for this device. You must deactivate on an actively installed system.';

var ERRORS_n1024 =  //kSAAuthorizeLicenseAlreadyDeactivated
'This license you have attempted to deactivate is already deactivated for this device.';

var ERRORS_n1025 =  //kSAAuthorizeFeatureNotFound
'';

var ERRORS_n1026 =  //kSAAuthorizeInvalidProduct
'It appears the product you are attempting to activate is invalid.';

var ERRORS_n1027 =  //kSAAuthorizeLicenseParameterMissing
'You must provide a license key to activate.';

var ERRORS_n1028 =  //kSAAuthorizeFingerprintParameterMissing
'It seems your attempt to activate was corrupted. ';

var ERRORS_n1029 =  //kSAAuthorizeIPParameterMissing
'';

var ERRORS_n1030 =  //kSAAuthorizeFeatureIDParameterMissing
'';

var ERRORS_n1031 =  //kSAAuthorizeMediumParameterMissing
'';

var ERRORS_n1032 =  //kSAAuthorizeUpgradeLicenseParameterMissing
'';

var ERRORS_n1033 =  //kSAAuthorizeGeneralError
'It appears we cannot reach the activation servers. Your application may be blocked by a personal firewall, or the activation servers may currently be offline. Please try again momentarily.';

var ERRORS_n1034 =  //kSAAuthorizeLicenseDisabled
'It appears the license you have attempted to activate has been disabled. Please contact the issuer of your key.';

var ERRORS_n1035 =  //kSAAuthorizeInvalidDNSName
'It appears the license you have attempted to activate is not valid for the vendor in question. Please check the license key and try again.';

var ERRORS_n1036 =  //kSACouldNotCreateActivationRequest
'A critical failure has occured during activation. Please restart the application and try again.';

var ERRORS_n1037 =  //kSAFailedToConnectToServer
'It appears we could not reach the activation servers. Your application may be blocked by a personal firewall, or the activation servers may currently be offline. Please try again momentarily.';

var ERRORS_n1038 =  //kSAHttpResponseEmpty
'It appears we were unable reach the activation servers. Your application may be blocked by a personal firewall, or the activation servers may currently be offline. Please try again momentarily.';

var ERRORS_n1039 =  //kSACouldNotCreateDeactivationRequest    
'A critical failure has occured during deactivation. Please restart the application and try again.';

var ERRORS_n1040 =  //kSALicenseKeyTextFileNotFound
'We have attempted to background activate this product; however, we were unable to find a local file containing the license key. Please check with your system administrator.';

var ERRORS_n1041 =  //kSAGetLicenseServicePathNotSpecified
'We could not start a trial period. It appears this software is incorrectly configured.';

var ERRORS_n1042 =  //kSATrialProductIdNotSpecified
'We were unable to start a trial period. It appears this software is incorrectly configured.';
	
var ERRORS_n1043 =  //kSACouldNotReadCert
'It seems the local environment for this program is incorrect. The activation could not continue.';
	
var ERRORS_n1044 =  //kSACertInvalidFormat - should never bubble up as 1044
'It seems the local environment for this program is incorrect. The activation could not continue.';

var ERRORS_n1045 =  //kSACertInvalidAfterMultipleAttempts
'We were unable to write data to the CSIDL_COMMON_APPDATA directory and cannot continue the activation. Please contact your application provider.';

var ERRORS_n1046 =  //kSATooManyTrials
'It appears the activation servers were unable to allow this trial because the system has had too many previous trials. If you feel this is in error, please contact your application provider.';
			
var ERRORS_n703  =  //Invalid activation response
'This is an invalid activation response. Please check the response, and try again.';
	
var ERRORS_n709  =  //Invalid activation response
'The activation response installed does not match the last activation request generated. You must upload the last request generated for this computer and then reinstall the response you receive.';

var ERRORS_p1  =  //Invalid activation response
'You must provide an activation response. Please try again.';
	
var ERRORS_n1900000 = //kSAERROR_HTTP_SEND_ERROR or kSAERROR_HTTP_CONNECTION_ERROR
'It appears we cannot reach the activation servers. Your application may be blocked by a personal firewall, or the activation servers may currently be offline. Please try again momentarily.';
	
var ERRORS_p2900 =
'An activation request could not be generated.';

var ERRORS_p2500 = //if not 2900, but > then 2500
'We could not read your activation response from the location specified.';

var ERRORS_p2400 = //if not 2900, but > then 2400
'We could not open your activation response file.';

var ERRORS_p2200 = //if not 2900, but > then 200
'We could not write to your activation request file.';

var ERRORS_p2100 =
'We could not create your activation request file.';


/*******************************************************
*  STATE.JS
*******************************************************/

var STATE_msgInvalidSignature =
'Your license file appears to be corrupted.';

var STATE_msgExpired =		
'Your free trial period is over.';

var STATE_msgGrace =
'Something is wrong with your license. The application has entered a grace period. ';

var STATE_msg1Hr = 
'You currently have 1 hour remaining in your trial.';

var STATE_msgCurrentlyHave =
'You currently have';

var STATE_msgHrsRemaining =
'hours remaining in your trial.';    

var STATE_msg1Min =
'You currently have 1 minute remaining in your trial.';

var STATE_msgMinsRemaining =
'minutes remaining  in your trial.';

var STATE_msgSecsRemaining =
'seconds remaining in your trial.';

var STATE_msgDaysOr =
'days or';

var STATE_msgRunsRemaining =
'runs remaining.';

var STATE_msgDaysRemaining =
'days remaining in your trial.';

var STATE_msg1Hr_2 =
'You currently have 1 minute';

var STATE_msgHrLabel =
'hours';

var STATE_msg1Min_2 =
'You currently have 1 minute';

var STATE_msgMinLabel =
'minutes';

var STATE_msgSecondsLabel =
'seconds';

var STATE_msg1RunRemaining = 
'or 1 run remaining.';

var STATE_msgOrLabel =
'or';

var STATE_msgRunsRemaining_2 = 
'runs remaining.';

var STATE_closeLabel =
' Close ';