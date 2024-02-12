Action()
{
//	char login[255] = {0};
//	int i = 0 ,j = 0;
//	
//	char RandomLetter[3] = {0};
//	//int RandomNum = "0123456789"[random()%9];
//	
//	for(i =0; i < 5; i++)
//	{
//		RandomLetter[i] = rand()%26+'a'; 
//		for(j =0; j < 5; j++) { RandomNum[j] += rand()%8; }
//	}
//	
//	lr_save_string(lr_eval_string("{login}"), "login");
//	sprintf(login, "%s%c%d", lr_eval_string("{login}"), RandomLetter, RandomNum);
//	
//	lr_save_string(login,"newlogin");
//	
//	for (i = 0; i < 9; i++) { login[i] = 'A' + rand() % 26; }
//	login[9] = '\0';
//		
//	lr_save_string(login, "newlogin");
	
	char name[10]={0};
	char newlastName[10]={0};
	char newfirstName[10]={0};
	int i, j;
	
	for(i = 0; i < 9; i++)
	{
		name[i] = rand()%26+'a';
	}
	
		for(j = 0; j < 5; j++)
	{
		newlastName[j] = rand()%26+'a';
		newfirstName[j] = rand()%26+'a';
	}
		
	lr_save_string(name,"name");
	lr_save_string(newlastName,"newlastName");
	lr_save_string(newfirstName,"newfirstName");
	
	lr_start_transaction("UC6_Register_New_Users");

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
	
	
	lr_start_transaction("RegisterNewUser");

	
	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(4);
	
	web_url("sign up now", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("RegisterNewUser", LR_AUTO);

	
	
	lr_start_transaction("RegPage");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(9);

	web_reg_find("Text=Thank you, <b>{name}</b>, for registering and welcome to the Web Tours family.",LAST);
	
	web_submit_data("login.pl", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={name}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value={newfirstName}", ENDITEM, 
		"Name=lastName", "Value={newlastName}", ENDITEM, 
		"Name=address1", "Value={street}", ENDITEM, 
		"Name=address2", "Value={city}", ENDITEM, 
		"Name=register.x", "Value=71", ENDITEM, 
		"Name=register.y", "Value=11", ENDITEM, 
		LAST);
	
	lr_end_transaction("RegPage", LR_AUTO);

	
	
	lr_start_transaction("ContinueAfterReg");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_url("button_next.gif", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("ContinueAfterReg", LR_AUTO);

	lr_end_transaction("UC6_Register_New_Users", LR_AUTO);
	
	return 0;
}