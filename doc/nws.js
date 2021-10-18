function $id(id) { return document.getElementById(id); }

var UI = {
  Datestart:Date.now(),
  langue: -1, // -1 french
  calc: 2, // 1 KhiCAS, 2 Numworks, 3 TI Nspire CX
  calculator:0, // !=0 if hardware Numworks connected
  calculator_connected:false,
  nws_connect:function(){
    if (navigator.usb){
      //console.log('nws_connect 0');
      if (UI.calculator!=0)
	return;
      //console.log('nws_connect 1');
      function autoConnectHandler(e) {
	UI.calculator.stopAutoConnect();
	console.log('connected');
	UI.calculator_connected=true;
      }
      UI.calculator= new Numworks();
      navigator.usb.addEventListener("disconnect", function(e) {
	if (UI.calculator==0) return;
	UI.calculator.onUnexpectedDisconnect(e, function() {
	  UI.calculator_connected=false;
          UI.calculator=0;
	});
      });
      //console.log('nws_connect 2');
      UI.calculator.autoConnect(autoConnectHandler);
      //console.log('nws_connect 3');
    }
  },
  sig_check:async function(sig,data){
    // sig should be a list of lists of size 3 (name, length, hash)
    let i=0,l=sig.length;
    for (;i<l;++i){
      let cur=sig[i];
      console.log('sig_check',cur[1],data.byteLength);
      if (cur[1]>data.byteLength) continue;
      let dat=data.slice(0,cur[1]);
      let digest = await window.crypto.subtle.digest('SHA-256', dat);
      digest=Array.from(new Uint8Array(digest));
      console.log(cur[2],digest);
      let j=0;
      for (;j<32;++j){
	let tst=(digest[j]-cur[2][j]) % 256;
	// console.log(j,digest[j],cur[2][j]);
	if (tst)
	  break;
      }
      if (j==32){
	console.log('signature match',cur[0]);
	return true;
      }      
    }
    return false;
  },
  numworks_install_delta:function(){
    UI.calc=2;
    UI.nws_connect();
    window.setTimeout(UI.numworks_install_delta_,100);
  },
  numworks_install_delta_:async function(sigfile,rwcheck){
    if (UI.calculator==0 || !UI.calculator_connected){
      alert(UI.langue==-1?'Verifiez que la calculatrice Numworks est connectee':'Check that the Numworks calculator is connected');
      return -1;
    } 
    UI.calculator.device.startAddress = 0x08000000;
    let data=await UI.loadfile('delta.internal.bin');
    let res=await UI.calculator.device.do_download(UI.calculator.transferSize, data, false);
    UI.print('internal OK, erase external');
    UI.calculator.device.startAddress = 0x90000000;
    data=await UI.loadfile('delta.external.bin');
    res=await UI.calculator.device.do_download(UI.calculator.transferSize, data, false);
    UI.print('external OK, erase apps');
    UI.calculator.device.startAddress = 0x90200000;
    data=await UI.loadfile('apps.tar');
    res=await UI.calculator.device.do_download(UI.calculator.transferSize, data, false);
    UI.print('apps OK');
    alert(UI.langue==-1?'Installation terminee. Appuyer sur RESET a l\'arriere de la calculatrice':'Install success. Press RESET on the calculator back.');
    return 0;
  },
  loadfile:function(file) {
    return fetch(file).then(function(response) {
      if (!response.ok) {
        throw new Error("HTTP error, status = " + response.status);
      }
      return response.arrayBuffer();
    })
  },
  numworks_rescue:function(){
    alert(UI.langue==-1?'Connectez la calculatrice, appuyez sur la touche 6 de la calculatrice, enfoncez un stylo dans le bouton RESET au dos en laissant la touche 6 appuyee, relachez la touche 6, l\'ecran doit etre eteint et la diode rouge allumee':'Connect the calculator, press the 6 key on the calculator, press the RESET button on the back keeping the 6 key pressed, release the 6 key, the screen should be down and the led should be red');
    UI.calc=2;
    UI.nws_connect();
    window.setTimeout(UI.numworks_rescue_,100);
  },
  numworks_rescue_:async function(sigfile,rwcheck){
    if (UI.calculator==0 || !UI.calculator_connected){
      alert(UI.langue==-1?'Verifiez que la calculatrice Numworks est connectee':'Check that the Numworks calculator is connected');
      return -1;
    } 
    UI.calculator.device.startAddress = 0x20030000;
    let data=await UI.loadfile('recovery');
    await UI.calculator.device.clearStatus();
    let res=await UI.calculator.device.do_download(UI.calculator.transferSize, data, true);
    if (!res){
      alert(UI.langue==-1?'Echec de la mise en mode recuperation. Recommencez':'Rescue mode failure. Try again.');
      return res;
    }
    return numworks_install_delta();
 },
  numworks_certify:function(sigfile,rwcheck=false){
    UI.calc=2;
    UI.nws_connect();
    window.setTimeout(UI.numworks_certify_,100,sigfile,rwcheck);
  },
  numworks_certify_:async function(sigfile,rwcheck){
    if (UI.calculator==0 || !UI.calculator_connected){
      alert(UI.langue==-1?'Verifiez que la calculatrice Numworks est connectee':'Check that the Numworks calculator is connected');
      return -1;
    }
    if (rwcheck)
      alert(UI.langue==-1?'Le test va prendre une petite minute':'Test will take about 1 minute');
    else
      alert(UI.langue==-1?'Le test va prendre environ 20 secondes':'Test will take about 20 seconds');
    UI.print('========');
    let internal=await UI.calculator.get_internal_flash();
    //console.log(sigfile);
    let res=await UI.sig_check(sigfile,internal);
    if (!res){
      alert(UI.langue==-1?'Flash interne non certifiee':'Internal flash not certified');
      return 1;
    }
    UI.print('Internal flash OK');
    let external=await UI.calculator.get_external_flash();
    res=await UI.sig_check(sigfile,external);
    if (!res){
      alert(UI.langue==-1?'Flash externe non certifiee':'External flash not certified');
      return 2;
    }
    UI.print('External flash OK');
    let apps=await UI.calculator.get_apps();
    res=await UI.sig_check(sigfile,apps);
    if (!res){
      alert(UI.langue==-1?'Applications non certifiees':'Applications not certified');
      return 3;
    }
    UI.print('Apps OK');
    if (rwcheck){
      UI.print('R/W check');
      res=await UI.calculator.rw_check(0x90100000,0x100000);
      if (!res){
	alert(UI.langue==-1?'Echec du test lecture/ecriture':'Read/Write test failure');
	return 4;
      }
      UI.print('R/W OK');
    }
    alert(UI.langue==-1?'Firmware certifie':'Firmware certified');
    return 0;
  },
  htmlbuffer:'',
  htmlcheck:true,
  print:function(text){
    let element = $id('output');
    //console.log(text.charCodeAt(0));
    if (text.length == 1 && text.charCodeAt(0) == 12) {
      element.innerHTML = '';
      return;
    }
    if (text.length >= 1 && text.charCodeAt(0) == 2) {
      console.log('STX');
      UI.htmlcheck = false;
      UI.htmlbuffer = '';
      return;
    }
    if (text.length >= 1 && text.charCodeAt(0) == 3) {
      console.log('ETX');
      UI.htmlcheck = true;
      element.style.display = 'inherit';
      element.innerHTML += UI.htmlbuffer;
      UI.htmlbuffer = '';
      element.scrollTop = 99999;
      return;
    }
    if (UI.htmlcheck) {
      // These replacements are necessary if you render to raw HTML
      text = '' + text;
      console.log(text);
      text = text.replace(/&/g, "&amp;");
      text = text.replace(/</g, "&lt;");
      text = text.replace(/>/g, "&gt;");
      text = text.replace(/\n/g, '<br>');
      text += '<br>';
      element.style.display = 'inherit';
      element.innerHTML += text; // element.value += text + "\n";
      element.scrollTop = 99999; // focus on bottom
    } else UI.htmlbuffer += text;
    element.scrollIntoView();
  },
};

