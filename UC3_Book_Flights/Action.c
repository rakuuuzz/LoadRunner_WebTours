Action()
{
	int random;
	char flightTime[20];
	char flightId[10];
	char outbound_flight[50];
	
	lr_start_transaction("UC3_Book_Flights");

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
	
	
	
	lr_start_transaction("go_to_FlightsPage");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
		
	web_reg_save_param_ex("ParamName=City",
						  "LB=\<option value\=\"",
						  "RB=\">",
					  	  "Ordinal=ALL",
						  LAST);
	
	
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

	lr_start_transaction("ticket_Search");
	
	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	
	web_reg_find("Text=Find Flight",LAST);
	
	/*
	web_reg_save_param("outboundFlight",
				   "LB=name=\"outboundFlight\" value=\"",
				   "RB=\">",
				   "Ordinal=3",
				   LAST);
	*/
	
	web_reg_save_param_attrib(
				   "ParamName=outboundFlight",
				   "TagName=input",
				   "Extract=value",
				   "Name=outboundFlight",
				   "Ordinal=ALL",
				   "Type=radio",
				   SEARCH_FILTERS,
				   "IgnoreRedirections=No",
				   LAST);
	
	web_reg_save_param("flightId",         
				   "LB=name=\"outboundFlight\" value=\"",
				   "RB=;",
				   "Ord=ALL",
				   LAST);
	
	web_reg_save_param("flightTime",
		 		   "LB=<td align=\"center\">",
				   "RB=<td align=\"center\">$",
				   "Ord=ALL",
				   LAST);
	
	//<td align="center">  <td align="center">$
	
	web_reg_find("Text=Flight departing from <B>{CityDep}</B> to <B>{CityArr}</B> on <B>{departDate}</B>", LAST);
	
	web_submit_data("reservations.pl",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome",
		"Snapshot=t4.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=depart", "Value={CityDep}", ENDITEM,
		"Name=departDate", "Value={departDate}", ENDITEM,
		"Name=arrive", "Value={CityArr}", ENDITEM,
		"Name=returnDate", "Value={returnDate}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=findFlights.x", "Value=56", ENDITEM,
		"Name=findFlights.y", "Value=7", ENDITEM,
		"Name=.cgifields", "Value=roundtrip", ENDITEM,
		"Name=.cgifields", "Value=seatType", ENDITEM,
		"Name=.cgifields", "Value=seatPref", ENDITEM,
		LAST);

	lr_end_transaction("ticket_Search", LR_AUTO);
	
	
	random = rand()%(atoi(lr_eval_string("{flightId_count}")) - 1) + 1;
			
	sprintf(flightTime, "{flightTime_%d}", random);
	lr_save_string(lr_eval_string(flightTime), "flightTime_Id");
		
	sprintf(flightId, "{flightId_%d}", random);
	lr_save_string(lr_eval_string(flightId), "flightNum_Id");
	
	sprintf(outbound_flight, "{outboundFlight_%d}", random);
	lr_save_string(lr_eval_string(outbound_flight), "outboundFlight");
	

	lr_start_transaction("choose_Ticket");

	web_reg_find("Text=Payment Details",LAST);
	
	web_submit_data("reservations.pl_2",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t5.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=reserveFlights.x", "Value=50", ENDITEM,
		"Name=reserveFlights.y", "Value=10", ENDITEM,
		LAST);
	
	lr_end_transaction("choose_Ticket", LR_AUTO);
	
	
	lr_start_transaction("payment_Details");

	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(4);

	web_reg_find("Text=Invoice",LAST);
	web_reg_find("Text={flightTime_Id} : Flight {flightNum_Id} leaves {CityDep}  for {CityArr}", LAST);
	
	web_submit_data("reservations.pl_3",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t6.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=firstName", "Value={firstName}", ENDITEM,
		"Name=lastName", "Value={lastName}", ENDITEM,
		"Name=address1", "Value={street}", ENDITEM,
		"Name=address2", "Value={city}", ENDITEM,
		"Name=pass1", "Value= {firstName} {lastName}", ENDITEM,
		"Name=creditCard", "Value={creditCard}", ENDITEM,
		"Name=expDate", "Value={expDate}", ENDITEM,
		"Name=oldCCOption", "Value=", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=returnFlight", "Value=", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=buyFlights.x", "Value=30", ENDITEM,
		"Name=buyFlights.y", "Value=11", ENDITEM,
		"Name=.cgifields", "Value=saveCC", ENDITEM,
		LAST);
	
	lr_end_transaction("payment_Details", LR_AUTO);
	
	
	lr_start_transaction("logout");

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
	
	lr_end_transaction("logout", LR_AUTO);

	
	lr_end_transaction("UC3_Book_Flights", LR_AUTO);


	return 0;
}