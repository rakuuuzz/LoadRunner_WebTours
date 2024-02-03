Action()
{

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Site", 
		"cross-site");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("DNT", 
		"1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(5);

	web_submit_data("login.pl", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value=138274.520939652HVVctQfpzHAiDDDDtczHtpQHtAcf", ENDITEM, 
		"Name=username", "Value=rakuz", ENDITEM, 
		"Name=password", "Value=1234qwer", ENDITEM, 
		"Name=login.x", "Value=48", ENDITEM, 
		"Name=login.y", "Value=3", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);

	
	
	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");
	
		web_add_header("Origin", 
		"http://localhost:1080");

	web_add_header("Sec-Fetch-User", 
		"?1");

//	web_reg_save_param_regexp(
//        "ParamName=flightID",
//        "RegExp=name",
//        "Group=1",
//        "Ordinal=All",
//    	LAST);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	
		web_submit_data("itinerary.pl",
		"Action=http://localhost:1080/cgi-bin/itinerary.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl",
		"Snapshot=t4.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=flightID", "Value={flightID}", ENDITEM,
		"Name={DeleteID}", "Value=on", ENDITEM,
		"Name=removeFlights.x", "Value=55", ENDITEM,
		"Name=removeFlights.y", "Value=12", ENDITEM,
		"Name=.cgifields", "Value=6", ENDITEM,
		"Name=.cgifields", "Value=3", ENDITEM,
		"Name=.cgifields", "Value=7", ENDITEM,
		"Name=.cgifields", "Value=2", ENDITEM,
		"Name=.cgifields", "Value=8", ENDITEM,
		"Name=.cgifields", "Value=1", ENDITEM,
		"Name=.cgifields", "Value=4", ENDITEM,
		"Name=.cgifields", "Value=5", ENDITEM,
		LAST);

	return 0;
}