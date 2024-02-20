Action()
{

	lr_start_transaction("UC4_Itinerary_List");

	
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
	
	lr_start_transaction("search_Itinerary");


	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	

	web_reg_find("Text=User wants the intineraries.  Since user has already logged on",LAST);
	
	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
		
	lr_end_transaction("search_Itinerary", LR_AUTO);
	
	lr_start_transaction("go_to_FlightsPage");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	
	web_reg_save_param_ex("ParamName=City",
						  "LB=\<option value\=\"",
						  "RB=\">",
					  	  "Ordinal=ALL",
						  LAST);
	
	web_reg_find("Text=User has returned to the search page",LAST);
	
	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_save_string(lr_paramarr_random("City"),"CityDep");
	lr_save_string(lr_paramarr_random("City"),"CityArr");
	while (strcmp(lr_eval_string("{CityDep}"), lr_eval_string("{CityArr}")) == 0)
	{
    	lr_save_string(lr_paramarr_random("City"), "CityDep");
	}
	
	lr_end_transaction("go_to_FlightsPage", LR_AUTO);
	
	lr_end_transaction("UC4_Itinerary_List", LR_AUTO);


	return 0;
}