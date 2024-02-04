Action()
{
	lr_start_transaction("UC1_Login&Logout");

	lr_start_transaction("go_to_WebTours");


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

/*Correlation comment - Do not change!  Original value='138244.830862697HVVAQziptiHftczzfpiVAQcf' Name ='userSession' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=userSession",
		"TagName=input",
		"Extract=value",
		"Name=userSession",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);

	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
		
	lr_end_transaction("go_to_WebTours", LR_AUTO);
	
	
	
	lr_start_transaction("Login");

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

	lr_think_time(8);
	
	web_reg_find("Text=User password was correct",LAST);
	
	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={login}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=45", ENDITEM,
		"Name=login.y", "Value=15", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("Login", LR_AUTO);
	
	
	
	
	lr_start_transaction("Logout");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(4);

	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	
	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("Logout", LR_AUTO);

	
	lr_end_transaction("UC1_Login&Logout", LR_AUTO);

	return 0;
}
