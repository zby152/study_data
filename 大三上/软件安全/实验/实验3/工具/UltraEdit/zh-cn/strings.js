
/*******************************************************
*  ERRORS.JS
*  N -> - (negative)
*  P -> + (positive)
*******************************************************/

var ERRORS_LabelErrorCode =
'错误码';

var ERRORS_n1000 = //kSAAuthorizeInvalidProductID
'你尝试启动的产品似乎是无效的。';

var ERRORS_n1001 = //kSAAuthorizeMissingProductID
'你尝试启动的产品似乎是无效的。';

var ERRORS_n1002 = //kSAAuthorizeInvalidFingerprint
'你尝试启动的这份授权码似乎不属于这个产品。';

var ERRORS_n1003 = //kSAAuthorizeInvalidLicenseKey
"你尝试启动的授权码似乎无法辨识。请检查这份授权码并再试一次。";

var ERRORS_n1004 =  //kSAAuthorizeOverLicenseDenial
'似乎这份授权码已超过它的安装限制。这份授权码目前已启动太多系统。';

var ERRORS_n1005 =  //kSAAuthorizeOverLicenseWarning
'似乎这份授权码已非常接近安装限制。你只能再安装这个授权码到另外一个系统。';

var ERRORS_n1006 =  //kSAAuthorizeSuccess
'成功！感谢您。';

var ERRORS_n1007 =  //kSAAuthorizeFatalError
'似乎这个启动伺服器目前已离线或有问题。请稍后再试着启动一次。';

var ERRORS_n1008 =  //kSAAuthorizeReactivation
'成功！感谢您。';

var ERRORS_n1009 =  //kSAAuthorizeUpgradeOnly
'你可能无法使用这个授权码来启动这个产品。这个授权码只能用来升级。';

var ERRORS_n1010 =  //kSAAuthorizeSubscriptionExpired
'似乎这份授权码的订阅关联已到期。';

var ERRORS_n1011 =  //kSAAuthorizeTrialExpired
'似乎这份授权码的试用已到期。';

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
'你尝试反启动的这份授权不允许反启动。';

var ERRORS_n1023 =  //kSAAuthorizeLicenseNotActivatedForDevice
'你尝试反启动的这份授权目前并未在这个装置上启动。你必须在启动的安装系统中反启动。';

var ERRORS_n1024 =  //kSAAuthorizeLicenseAlreadyDeactivated
'你尝试反启动的这份授权已经在这个装置上反启动过。';

var ERRORS_n1025 =  //kSAAuthorizeFeatureNotFound
'';

var ERRORS_n1026 =  //kSAAuthorizeInvalidProduct
'你尝试启动的产品似乎是无效的。';

var ERRORS_n1027 =  //kSAAuthorizeLicenseParameterMissing
'你必须提供一份授权码才能启动。';

var ERRORS_n1028 =  //kSAAuthorizeFingerprintParameterMissing
'似乎你尝试的启动已损毁。';

var ERRORS_n1029 =  //kSAAuthorizeIPParameterMissing
'';

var ERRORS_n1030 =  //kSAAuthorizeFeatureIDParameterMissing
'';

var ERRORS_n1031 =  //kSAAuthorizeMediumParameterMissing
'';

var ERRORS_n1032 =  //kSAAuthorizeUpgradeLicenseParameterMissing
'';

var ERRORS_n1033 =  //kSAAuthorizeGeneralError
'似乎我们无法连线这个启动伺服器。你的应用程式可能被防火墙封锁，或这个启动伺服器目前离线。请过一阵子再试。';

var ERRORS_n1034 =  //kSAAuthorizeLicenseDisabled
'似乎你尝试启动的这份授权已被停用。请连络发行者并提供你的授权码。';

var ERRORS_n1035 =  //kSAAuthorizeInvalidDNSName
'似乎你尝试启动的这份授权不是有效，因为销售人员尚有疑虑。请检查这份授权码并再试一次。';

var ERRORS_n1036 =  //kSACouldNotCreateActivationRequest
'启动期间遇到一个关键性的失败。请重新启动这个应用程式并再试一次。';

var ERRORS_n1037 =  //kSAFailedToConnectToServer
'似乎我们无法连线这个启动伺服器。你的应用程式可能被防火墙封锁，或这个启动伺服器目前离线。请过一阵子再试。';

var ERRORS_n1038 =  //kSAHttpResponseEmpty
'似乎我们无法连线这个启动伺服器。你的应用程式可能被防火墙封锁，或这个启动伺服器目前离线。请过一阵子再试。';

var ERRORS_n1039 =  //kSACouldNotCreateDeactivationRequest    
'反启动期间遇到一个关键性的失败。请重新启动这个应用程式并再试一次。';

var ERRORS_n1040 =  //kSALicenseKeyTextFileNotFound
'我们已尝试在背景启动这个产品；不过我们找不到一个包含这份授权码的本机档案。请跟你的系统管理员核对一下。';

var ERRORS_n1041 =  //kSAGetLicenseServicePathNotSpecified
'无法开始试用期。似乎是这个软体的配置不正确。';

var ERRORS_n1042 =  //kSATrialProductIdNotSpecified
'无法开始试用期。似乎是这个软体的配置不正确。';
	
var ERRORS_n1043 =  //kSACouldNotReadCert
'似乎是这个程式的本地环境不正确。启动无法继续。';
	
var ERRORS_n1044 =  //kSACertInvalidFormat - should never bubble up as 1044
'似乎是这个程式的本地环境不正确。启动无法继续。';

var ERRORS_n1045 =  //kSACertInvalidAfterMultipleAttempts
'无法写入资料到 CSIDL_COMMON_APPDATA 目录并且无法继续启动。请连络你的应用程式提供者。';

var ERRORS_n1046 =  //kSATooManyTrials
'似乎这个启动伺服器无法通过这个试用，因为这个系统之前已有太多次试用。如果你认为这是个错误，请连络你的应用程式提供人员。';
			
var ERRORS_n703  =  //Invalid activation response
'这是一个无效的启动回应。请检查这个回应并再试一次。';
	
var ERRORS_n709  =  //Invalid activation response
'安装的这个启动回应与上次所产生的启动请求不符。你必须上传上次为这部电脑所产生的请求，然后重新安装你所收到的回应。';

var ERRORS_p1  =  //Invalid activation response
'你必须提供一个启动回应。请再试一次。';
	
var ERRORS_n1900000 = //kSAERROR_HTTP_SEND_ERROR or kSAERROR_HTTP_CONNECTION_ERROR
'似乎我们无法连线这个启动伺服器。你的应用程式可能被防火墙封锁，或这个启动伺服器目前离线。请过一阵子再试。';
	
var ERRORS_p2900 =
'无法产生启动请求。';

var ERRORS_p2500 = //if not 2900, but > then 2500
'无法从这个指定的位置读取你的启动回应。';

var ERRORS_p2400 = //if not 2900, but > then 2400
'无法开启你的启动回应档案。';

var ERRORS_p2200 = //if not 2900, but > then 200
'无法写入你的启动请求档案。';

var ERRORS_p2100 =
'无法建立你的启动请求档案。';


/*******************************************************
*  STATE.JS
*******************************************************/

var STATE_msgInvalidSignature =
'你的授权档案似乎已损毁。';

var STATE_msgExpired =		
'已超过你的免费试用期限。';

var STATE_msgGrace =
'你的授权有一些问题。这个应用程式已进入宽限期。';

var STATE_msg1Hr = 
'目前你的试用期只剩下 1 小时。';

var STATE_msgCurrentlyHave =
'你目前还有';

var STATE_msgHrsRemaining =
'小时的剩余试用期。';    

var STATE_msg1Min =
'目前你的试用期只剩下 1 分钟。';

var STATE_msgMinsRemaining =
'分钟的剩余试用期。';

var STATE_msgSecsRemaining =
'秒钟的剩余试用期。';

var STATE_msgDaysOr =
'天或';

var STATE_msgRunsRemaining =
'次的剩余。';

var STATE_msgDaysRemaining =
'天的剩余试用期。';

var STATE_msg1Hr_2 =
'你目前还有 1 分钟';

var STATE_msgHrLabel =
'小时';

var STATE_msg1Min_2 =
'你目前还有 1 分钟';

var STATE_msgMinLabel =
'分钟';

var STATE_msgSecondsLabel =
'秒钟';

var STATE_msg1RunRemaining = 
'或剩下执行 1 次。 ';

var STATE_msgOrLabel =
'或';

var STATE_msgRunsRemaining_2 = 
'次的剩余。';

var STATE_closeLabel =
' 关闭 ';