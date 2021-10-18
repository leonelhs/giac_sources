function $id(id) { return document.getElementById(id); }

var UI = {
  nws_progress:0,
  nws_progresslegend:0,
  Datestart:Date.now(),
  langue: -1, // -1 french
  calc: 2, // 1 KhiCAS, 2 Numworks, 3 TI Nspire CX
  calculator:0, // !=0 if hardware Numworks connected
  calculator_connected:false,
  nws_connect:function(){
    UI.nws_progress=$id('plog');
    UI.nws_progresslegend=$id('ploglegend');
    if (navigator.usb){
      //console.log('nws_connect 0');
      UI.calculator=0;
      UI.calculator_connected=false;
      //console.log('nws_connect 1');
      function autoConnectHandler(e) {
	UI.calculator.stopAutoConnect();
	console.log('connected');
	UI.calculator_connected=true;
      }
      UI.calculator= new Numworks();
      console.log('nws_connect',UI.calculator);
      navigator.usb.addEventListener("disconnect", function(e) {
	if (UI.calculator==0) return;
	UI.calculator.onUnexpectedDisconnect(e, function() {
	  UI.calculator_connected=false;
          UI.calculator=0;
	});
      });
      //console.log('nws_connect 2');
      UI.calculator.autoConnect(autoConnectHandler);
      return UI.calculator;
      //console.log('nws_connect 3');
    }
  },
  nws_rescue_connect:async function(){
    if (navigator.usb){
      //console.log('nws_rescue_connect 0');
      UI.calculator=0;
      UI.calculator_connected=false;      //console.log('nws_rescue_connect 1');
      function autoConnectHandler(e) {
	UI.calculator.stopAutoConnect();
	console.log('rescue connected');
	UI.calculator_connected=true;
      }
      UI.calculator= new Numworks.Recovery();
      console.log('nws_rescue_connect',UI.calculator);
      navigator.usb.addEventListener("rescue disconnect", function(e) {
	if (UI.calculator==0) return;
	UI.calculator.onUnexpectedDisconnect(e, function() {
	  UI.calculator_connected=false;
          UI.calculator=0;
	});
      });
      //console.log('nws_rescue_connect 2');
      if (await UI.calculator.autoConnect(autoConnectHandler)==-1){
	return -1;
      }
      //console.log('nws_rescue_connect 3');
      return 0;
    }
  },
  sig_check:async function(sig,data,fname){
    // sig should be a list of lists of size 3 (name, length, hash)
    let i=0,l=sig.length;
    for (;i<l;++i){
      let cur=sig[i];
      if (cur[0]!=fname) continue;
      console.log('sig_check',i,cur[1],data.byteLength);
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
  numworks_load:function(backup=false){
    UI.calc=2;
    UI.nws_connect();
    window.setTimeout(UI.numworks_load_,100,backup);
  },
  numworks_load_: async function(backup){
    console.log(UI.calculator,UI.calculator_connected);
    if (UI.calculator==0 || !UI.calculator_connected){
      alert(UI.langue==-1?'Verifiez que la calculatrice Numworks est connectee':'Check that the Numworks calculator is connected');
      if (UI.calculator) UI.calculator.stopAutoConnect();
      return;
    }
    if (backup){
      let pinfo = await UI.calculator.getPlatformInfo();
        
      let storage_blob = await UI.calculator.__retreiveStorage(pinfo["storage"]["address"], pinfo["storage"]["size"]);
      filename = "backup.nws";
      saveAs(storage_blob.slice(0,32768), filename);
      return;
    }
    let storage = await UI.calculator.backupStorage();
    let rec=storage.records,j=0,s='Choisissez un numero parmi ';
    for (;j<rec.length;++j){
      s+=j;
      s+=':'+rec[j].name+', ';
    }
    let p=prompt(s),n=0;
    if (!p) return;
    let l=p.length;
    for (j=0;j<l;++j){
      if (p[j]<'0' || p[j]>'9'){ alert(UI.langue==-1?'Nombre invalide':'Invalid number'); return ;}
      n*=10;
      n+=p.charCodeAt(j)-48;
    }
    if (n>=rec.length){ alert(UI.langue==-1?'Choix invalide':'Invalide choice'); return; }
    s=rec[n].code; p=rec[n].name;
    let blob = new Blob([s], {type: "text/plain;charset=utf-8"});
    filename = p + ".py";
    saveAs(blob, filename);
  },
  loadFile:function(file){
    let reader = new FileReader();
    reader.onerror = function (evt) { }
    if (file.name.length>4 && file.name.substr(file.name.length-4,4)==".nws"){
      if (!confirm(UI.langue==-1?'Remplacer tous les scripts de la calculatrice?':'Overwrite all calculator scripts?'))
	return;
      reader.readAsArrayBuffer(file);
    }
    else
      reader.readAsText(file, "UTF-8");
    reader.onload = function (evt) { UI.numworks_save(file.name,evt.target.result);}
  },
  numworks_save:function(filename,S){
    //console.log(filename,S); return;
    UI.nws_connect();
    window.setTimeout(UI.numworks_save_,100,filename,S);
  },
  numworks_save_:async function(filename,S){
    if (UI.calculator==0 || !UI.calculator_connected){
      alert(UI.langue==-1?'Verifiez la connection de la calculatrice':'Check calculator connection');
      if (UI.calculator) UI.calculator.stopAutoConnect();
      return -1;
    }
    if (filename.length>4 && filename.substr(filename.length-4,4)==".nws"){
      let pinfo = await UI.calculator.getPlatformInfo();
      UI.calculator.device.startAddress = pinfo["storage"]["address"];
      console.log(UI.calculator.device.startAddress,S); // return;
      let res=await UI.calculator.device.do_download(UI.calculator.transferSize, S, false);
      return res;
    }
    if (filename.length>3 && filename.substr(filename.length-3,3)==".py")
      filename=filename.substr(0,filename.length-3);
    let storage = await UI.calculator.backupStorage();
    let rec=storage.records,j=0;
    for (;j<rec.length;++j){
      if (rec[j].name==filename){
	if (!confirm((UI.langue==-1?'? Ecraser ':'? Overwrite ')+rec[j].name))
	  return;
	rec[j].code=S;
	break;
      }
    }
    if (j==rec.length)
      rec.push({"name": filename, "type":"py", "autoImport": false, "code": S});
    await UI.calculator.installStorage(storage, function() {
      // Do stuff after writing to the storage is done
      console.log(filename+'.py saved to Numworks');
    });
    return 0;
  },    
  numworks_install_delta:function(){
    UI.calc=2;
    UI.nws_connect();
    window.setTimeout(UI.numworks_install_delta_,100);
  },
  numworks_install_delta_:async function(do_backup){
    if (UI.calculator==0 || !UI.calculator_connected){
      alert(UI.langue==-1?'Verifiez que la calculatrice Numworks est connectee':'Check that the Numworks calculator is connected');
      if (UI.calculator) UI.calculator.stopAutoConnect();
      return -1;
    } 
    UI.calculator.device.startAddress = 0x08000000;
    UI.calculator.device.logProgress(0,'internal');
    let data=await UI.loadfile('delta.internal.bin');
    let res=await UI.calculator.device.do_download(UI.calculator.transferSize, data, false);
    UI.print('=========== installing KhiCAS');
    UI.print('internal OK, erase/write external, wait about 1/2 minute');
    UI.calculator.device.startAddress = 0x90000000;
    data=await UI.loadfile('delta.external.bin');
    UI.calculator.device.logProgress(0,'external');
    res=await UI.calculator.device.do_download(UI.calculator.transferSize, data, false);
    UI.print('external OK, erase/write apps, wait about 2 minutes');
    UI.calculator.device.startAddress = 0x90200000;
    UI.calculator.device.logProgress(0,'apps');
    data=await UI.loadfile('apps.tar');
    res=await UI.calculator.device.do_download(UI.calculator.transferSize, data, false);
    UI.print('apps OK, press RESET on calculator back');
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
  numworks_rescue:async function(){
    alert(UI.langue==-1?'Connectez la calculatrice, appuyez sur la touche 6 de la calculatrice, enfoncez un stylo dans le bouton RESET au dos en laissant la touche 6 appuyee, relachez la touche 6, l\'ecran doit etre eteint et la diode rouge allumee':'Connect the calculator, press the 6 key on the calculator, press the RESET button on the back keeping the 6 key pressed, release the 6 key, the screen should be down and the led should be red');
    UI.calc=2;
    let res=await UI.nws_rescue_connect();
    if (res==-1){
      return;
    }
    window.setTimeout(UI.numworks_rescue_,1000);
  },
  numworks_rescue_:async function(sigfile,rwcheck){
    if (UI.calculator==0 || !UI.calculator_connected){
      alert(UI.langue==-1?'Verifiez que la calculatrice Numworks est connectee':'Check that the Numworks calculator is connected');
      //console.log('numworks_rescue_',UI.calculator);
      if (UI.calculator) UI.calculator.stopAutoConnect();
      UI.calculator=0;
      return -1;
    }
    UI.print(UI.langue==-1?'Envoi du mode de recuperation, patientez environ 15 secondes':'Sending rescue mode, wait about 15 secondes');
    UI.calculator.device.startAddress = 0x20030000;
    let data=await UI.loadfile('recovery');
    await UI.calculator.device.clearStatus();
    await UI.calculator.device.do_download(UI.calculator.transferSize, data, true);
    let tmp=confirm(UI.langue==-1?'La calculatrice devrait etre en mode recuperation. Installer KhiCAS+Delta?':'Calculator should be in rescue mode. Send KhiCAS+Delta.');
    if (tmp)
      UI.numworks_install_delta();
 },
  numworks_certify:function(sigfile,rwcheck=false){
    UI.calc=2;
    UI.nws_connect();
    window.setTimeout(UI.numworks_certify_,100,sigfile,rwcheck);
  },
  numworks_certify_:async function(sigfile,rwcheck){
    if (UI.calculator==0 || !UI.calculator_connected){
      alert(UI.langue==-1?'Verifiez que la calculatrice Numworks est connectee':'Check that the Numworks calculator is connected');
      if (UI.calculator) UI.calculator.stopAutoConnect();
      return -1;
    }
    if (rwcheck)
      if (!confirm(UI.langue==-1?"Ce test necessite l'accord du proprietaire de la calculatrice, il dure environ 1 minute. Poursuivre?":'This test requires the calculator owner authorization. It will take about 1 minute. Perform?'))
	return -1;
    //else alert(UI.langue==-1?'Le test va prendre environ 20 secondes':'Test will take about 20 seconds');
    UI.print('========');
    let internal=await UI.calculator.get_internal_flash();
    //console.log(sigfile);
    let res=await UI.sig_check(sigfile,internal,'delta.internal.bin');
    if (!res){
      alert(UI.langue==-1?'Flash interne non certifiee. Cliquer sur installer KhiCAS pour installer un firmware certifie.':'Internal flash not certified');
      return 1;
    }
    UI.print('Internal flash OK');
    let external=await UI.calculator.get_external_flash();
    res=await UI.sig_check(sigfile,external,'delta.external.bin');
    if (!res){
      alert(UI.langue==-1?'Flash externe non certifiee. Cliquer sur installer KhiCAS pour installer un firmware certifie.':'External flash not certified');
      return 2;
    }
    UI.print('External flash OK');
    let apps=await UI.calculator.get_apps();
    res=await UI.sig_check(sigfile,apps,'apps.tar');
    if (!res){
      alert(UI.langue==-1?'Applications non certifiees. Cliquer sur installer KhiCAS pour installer un firmware certifie.':'Applications not certified');
      return 3;
    }
    UI.print('Apps OK');
    if (rwcheck){
      UI.print('R/W check');
      res=await UI.calculator.rw_check(0x90120000,0xe0000);
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

