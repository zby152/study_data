function handleError()
{
	//window.open("http://salivesupport.uniloc.com/codesupport/error.aspx?code=" + window.external.MyError + "&customername=" + window.external.CustomerName + "&productname=" + window.external.ProductName);
	window.open("http://www.ultraedit.com/activation/error.php?code=" + window.external.MyError + "&customername=" + window.external.CustomerName + "&productname=" + window.external.ProductName);
}

function handleBack()
{
	history.go(-1);
}


function getErrorText(code)
{
	var val="";
	
	if (code == -1000) //kSAAuthorizeInvalidProductID
	{
		val = ERRORS_n1000;
	}

	if (code == -1001) //kSAAuthorizeMissingProductID
	{
		val = ERRORS_n1001;
	}

	if (code == -1002) //kSAAuthorizeInvalidFingerprint
	{
			val = ERRORS_n1002;
	}

	if (code == -1003) //kSAAuthorizeInvalidLicenseKey
	{
			val = ERRORS_n1003;
	}

	if (code == -1004) //kSAAuthorizeOverLicenseDenial
	{
			val = ERRORS_n1004;
	}

	if (code == -1005) //kSAAuthorizeOverLicenseWarning
	{
			val = ERRORS_n1005;
	}

	if (code == -1006) //kSAAuthorizeSuccess
	{
			val = ERRORS_n1006;
	}

	if (code == -1007) //kSAAuthorizeFatalError
	{
			val = ERRORS_n1007;
	}

	if (code == -1008) //kSAAuthorizeReactivation
	{
			val = ERRORS_n1008;
	}

	if (code == -1009) //kSAAuthorizeUpgradeOnly
	{
			val = ERRORS_n1009;
	}

	if (code == -1010) //kSAAuthorizeSubscriptionExpired
	{
			val = ERRORS_n1010;
	}
	if (code == -1011) //kSAAuthorizeTrialExpired
	{
			val = ERRORS_n1011;
	}
	if (code == -1012) //kSAAuthorizeFeatureSubscriptionExpired
	{
			val = ERRORS_n1012;
	}
	if (code == -1013) //kSAAuthorizeFeatureTrialExpired
	{
			val = ERRORS_1013;
	}
	if (code == -1014) //kSAAuthorizeFeatureTrialElapsed
	{
			val = ERRORS_n1014;
	}
	if (code == -1015) //kSAAuthorizeInvalidUpgradeLicenseKey
	{
			val = ERRORS_n1015;
	}
	if (code == -1016) //kSAAuthorizeActivationOnly
	{
			val = ERRORS_n1016;
	}
	if (code == -1017) //kSAAuthorizeInvalidUpgradeOptionTrial
	{
			val = ERRORS_n1017;
	}
	if (code == -1018) //kSAAuthorizeInvalidUpgradeOptionSubscription
	{
			val = ERRORS_n1018;
	}
	if (code == -1019) //kSAAuthorizeBaseLicenseDeactivated
	{
			val = ERRORS_n1019;
	}
	if (code == -1020) //kSAAuthorizeBaseLicenseNotActivated
	{
			val = ERRORS_n1020;
	}
	if (code == -1021) //kSAAuthorizeUpgradeProductMismatch
	{
			val = ERRORS_n1021;
	}
	if (code == -1022) //kSAAuthorizeDeactivationNotValidActionForLicense
	{
			val = ERRORS_n1022;
	}
	if (code == -1023) //kSAAuthorizeLicenseNotActivatedForDevice
	{
			val = ERRORS_n1023;
	}
	if (code == -1024) //kSAAuthorizeLicenseAlreadyDeactivated
	{
			val = ERRORS_n1024;
	}
	if (code == -1025) //kSAAuthorizeFeatureNotFound
	{
			val = ERRORS_n1025;
	}
	if (code == -1026) //kSAAuthorizeInvalidProduct
	{
			val = ERRORS_n1026;
	}
	if (code == -1027) //kSAAuthorizeLicenseParameterMissing
	{
			val = ERRORS_n1027;
	}
	if (code == -1028) //kSAAuthorizeFingerprintParameterMissing
	{
			val = ERRORS_n1028;
	}
	if (code == -1029) //kSAAuthorizeIPParameterMissing
	{
			val = ERRORS_n1029;
	}
	if (code == -1030) //kSAAuthorizeFeatureIDParameterMissing
	{
			val = ERRORS_n1030;
	}
	if (code == -1031) //kSAAuthorizeMediumParameterMissing
	{
			val = ERRORS_n1031;
	}
	if (code == -1032) //kSAAuthorizeUpgradeLicenseParameterMissing
	{
			val = ERRORS_n1032;
	}
	if (code == -1033) //kSAAuthorizeGeneralError
	{
			val = ERRORS_n1033;
	}
	if (code == -1034) //kSAAuthorizeLicenseDisabled
	{
			val = ERRORS_n1034;
	}
	if (code == -1035) //kSAAuthorizeInvalidDNSName
	{
			val = ERRORS_n1035;
	}


	if (code == -1036) //kSACouldNotCreateActivationRequest
	{
			val = ERRORS_n1036;
	}

	if (code == -1037) //kSAFailedToConnectToServer
	{
			val = ERRORS_n1037;
	}

	if (code == -1038) //kSAHttpResponseEmpty
	{
			val = ERRORS_n1038;
	}

	if (code == -1039) //kSACouldNotCreateDeactivationRequest    
	{
			val = ERRORS_n1039;
	}


	if (code == -1040) //kSALicenseKeyTextFileNotFound
	{
			val = ERRORS_n1040;
	}

	if (code == -1041) //kSAGetLicenseServicePathNotSpecified
	{
			val = ERRORS_n1041;
	}

	if (code == -1042) //kSATrialProductIdNotSpecified
	{
			val = ERRORS_n1042;
	}
	
	if (code == -1043) //kSACouldNotReadCert
	{
			val = ERRORS_n1043;
	}
	
	if (code == -1044) //kSACertInvalidFormat - should never bubble up as 1044
	{
			val = ERRORS_n1044;
	}

	if (code == -1045) //kSACertInvalidAfterMultipleAttempts
	{
			val = ERRORS_n1045;
	}

	if (code == -1046) //kSATooManyTrials
	{
			val = ERRORS_n1046;
	}
			
	
	if (code == -703 ) //Invalid activation response
	{
			val = ERRORS_n703;
	}
	

	if (code == -709 ) //Invalid activation response
	{
			val = ERRORS_n709;
	}


	if (code == 1 ) //Invalid activation response
	{
			val = ERRORS_p1;
	}
	
	//if val is blank, might be a special case, if not return.
	if (val =="")
	{
	
		return val += " " + ERRORS_LabelErrorCode + ": " + code;
	}
	
	
	if (code < -1900000) //kSAERROR_HTTP_SEND_ERROR or kSAERROR_HTTP_CONNECTION_ERROR
	{
		val = ERRORS_n1900000;
	}
	
	if (code == 2900)
	{
		val = ERRORS_p2900;
	}
	else if (code > 2500) //if not 2900, but > then 2500
	{
		val = ERRORS_p2500;
	}
	else if (code > 2400) //if not 2900, but > then 2400
	{
		val = ERRORS_p2400;
	}
	else if (code > 2200) //if not 2900, but > then 200
	{
		val = ERRORS_p2200;
	}
	else if (code > 2100)
	{
		val = ERRORS_p2100;
	}
	
	return val += " " + ERRORS_LabelErrorCode + ": " + code;

}