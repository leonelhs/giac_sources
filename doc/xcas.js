var UI ={
  mailto:'',
  from:'',
  ready:false,
  focusaftereval:true,
  docprefix:"http://www-fourier.ujf-grenoble.fr/%7eparisse/giac/doc/fr/cascmd_fr/",
  base_url:"http://www-fourier.ujf-grenoble.fr/%7eparisse/",
  focused:entree,
  savefocused:entree,
  usecm:true,
  fixeddel:false,
  kbdshift:false,
  usemathjax:false,
  prettyprint:true,
  qa:false,
  histcount:0,
  selection:'',
  langue:-1,
  canvas_w:350,
  canvas_h:200,
  canvas_lastx:0,
  canvas_lasty:0,
  canvas_pushed:false,
  gr2d_ncanvas:0,
  initconfigstring:'',
  python_mode:false,
  python_indent:4,
  xtn:'x', // var name, depends on last app
  sleep:function(miliseconds) {
    var currentTime = new Date().getTime();
    while (currentTime + miliseconds >= new Date().getTime()) {
    }
  },
  is_touch_device:function() {
    return (('ontouchstart' in window)
	    || (navigator.MaxTouchPoints > 0)
	    || (navigator.msMaxTouchPoints > 0));
  },
  assistant_list:['pour','tantque','solve','rsolve','fixe','test','prog','seq','plotpolar','series','limit','int','sum','diff','tabvarfunc','tabvarparam','plotfunc1var','plotfunc2var','plotparam','plotparam2var','plotimplicit','plotfield','desolve','matr','rand'
		 ],
  assistant_close:function(){
    var t=UI.assistant_list;
    var s=t.length;
    for (var i=0;i<s;i++){
      document.getElementById('assistant_'+t[i]).style.display='none';
    }
  },
  assistant_ok:function(){
    var t=UI.assistant_list;
    var s=t.length;
    for (var i=0;i<s;i++){
      var tmp=document.getElementById('assistant_'+t[i]);
      if (tmp.style.display=='block'){
	tmp='UI.assistant_'+t[i]+'_ok()';
	//console.log(tmp);
	eval(tmp); return true;
      }
    }
    return false;
  },
  assistant_pour_ok:function(){
    UI.focused=UI.savefocused;
    var st=document.getElementById('pourvarstep').value;
    if (UI.python_mode){
      UI.insert(UI.focused,'\nfor '+document.getElementById('pourvarname').value+' in range('+document.getElementById('pourvarmin').value+','+document.getElementById('pourvarmax').value);
      if (st.length) st=','+st;
      UI.insert(UI.focused,st+'):');
      UI.indentline(UI.focused);
      UI.insert(UI.focused,'\n');     
      UI.indentline(UI.focused);
    }
    else {
      var tmp='\npour '+document.getElementById('pourvarname').value+' de '+document.getElementById('pourvarmin').value+' jusque '+document.getElementById('pourvarmax').value;
      //console.log(tmp);
      UI.insert(UI.focused,tmp);
      UI.indentline(UI.focused);
      if (st.length) UI.insert(UI.focused,' pas '+st);
      UI.insert(UI.focused,' faire\n\nfpour;');
      UI.indentline(UI.focused);
      UI.moveCaretUpDown(UI.focused,-1);
      UI.indentline(UI.focused);
    }
    UI.focused.focus();
    document.getElementById('assistant_pour').style.display='none';
    document.getElementById('assistant_boucle').style.display='none';
  },
  assistant_tantque_ok:function(){
    UI.focused=UI.savefocused;
    if (UI.python_mode){
      UI.insert(UI.focused,'\nwhile '+document.getElementById('tantquecond').value+':');
      UI.indentline(UI.focused);
      UI.insert(UI.focused,'\n');
    }
    else {
      UI.insert(UI.focused,'\ntantque '+document.getElementById('tantquecond').value+' faire\n\nftantque;');
      UI.indentline(UI.focused);
      UI.moveCaretUpDown(UI.focused,-1);
      UI.indentline(UI.focused);
      UI.moveCaretUpDown(UI.focused,-1);
      UI.indentline(UI.focused);
      UI.moveCaretUpDown(UI.focused,1);
    }
    UI.focused.focus();
    document.getElementById('assistant_tantque').style.display='none';
    document.getElementById('assistant_boucle').style.display='none';
  },
  assistant_solve_ok:function(){
    UI.focused=UI.savefocused;if(document.getElementById('solveC').style.display=='inline' ) UI.insert(UI.focused,'c');if(document.getElementById('solvenum').style.display=='inline' ) UI.insert(UI.focused,'f');UI.insert(UI.focused,'solve('+document.getElementById('solveeq').value);UI.indentline(UI.focused);var tmp=document.getElementById('solvevar').value; if (tmp.length) UI.insert(UI.focused,','+tmp);UI.insert(UI.focused,')'); document.getElementById('assistant_solve').style.display='none';},
  assistant_rsolve_ok:function(){
    UI.focused=UI.savefocused;UI.insert(UI.focused,'rsolve('+document.getElementById('rsolveeq').value+','+document.getElementById('rsolvevar').value);var tmp=document.getElementById('rsolveinit').value; if (tmp.length) UI.insert(UI.focused,',['+tmp+']');UI.insert(UI.focused,')'); document.getElementById('assistant_rsolve').style.display='none';document.getElementById('assistant_suites').style.display='none';},
  assistant_desolve_ok:function(){
    UI.focused=UI.savefocused;var tmpeq=document.getElementById('desolveeq').value ;var tmpt=document.getElementById('desolvevar').value ;var tmpy=document.getElementById('desolvey').value ; var tmp=document.getElementById('desolveinit').value; if (tmp.length) tmp='desolve(['+tmpeq+','+tmp+']'; else tmp='desolve('+tmpeq; tmp+=','+tmpt+','+tmpy+')';UI.insert(UI.focused,tmp); document.getElementById('assistant_desolve').style.display='none';},
  assistant_fixe_ok:function(){
    UI.focused=UI.savefocused;var tmp= document.getElementById('rsolvef').value ;if (tmp.length){tmp+=':='+ document.getElementById('rsolvevarf').value+'->'+document.getElementById('rsolveexpr').value+';\nplotseq('+tmp+'('+document.getElementById('rsolvevarf').value+')';} else tmp='plotseq('+document.getElementById('rsolveexpr').value; tmp+=','+document.getElementById('rsolvevarf').value+'=';var tmp1=document.getElementById('rsolvemin').value;if (tmp1.length) tmp+='['+document.getElementById('rsolveu0').value+','+tmp1+','+document.getElementById('rsolvemax').value+']'; else tmp+=document.getElementById('rsolveu0').value;tmp+=','+document.getElementById('rsolven').value+')'; UI.insert(UI.focused,tmp);document.getElementById('assistant_fixe').style.display='none'; document.getElementById('assistant_suites').style.display='none';},
  assistant_test_ok:function(){
    UI.focused=UI.savefocused;
    if (UI.python_mode){
      UI.insert(UI.focused,'\nif '+document.getElementById('sicond').value+':');
      UI.indentline(UI.focused);
      UI.insert(UI.focused,'\n'+document.getElementById('sialors').value);
    } else UI.insert(UI.focused,'\nsi '+document.getElementById('sicond').value+' alors '+document.getElementById('sialors').value);
    UI.indentline(UI.focused);
    var tmp=document.getElementById('sisinon').value;
    if (tmp.length){
      if (UI.python_mode){
	UI.indentline(UI.focused);
	UI.insert(UI.focused,'\nelse:')
	UI.indentline(UI.focused); // should remove 2 spaces at start
	UI.insert(UI.focused,'\n'+tmp);
      } else { UI.insert(UI.focused,' sinon '+tmp);UI.insert(UI.focused,' fsi;\n'); }
    }
    else {
      if (!UI.python_mode)
	UI.insert(UI.focused,' fsi;\n');
    }
    UI.indentline(UI.focused);UI.funcoff();
    UI.focused.focus();
    document.getElementById('assistant_test').style.display='none';
  },
  assistant_prog_ok:function(){
    UI.focused=UI.savefocused;
    var loc=document.getElementById('localvars').value;
    var fc=document.getElementById('funcname').value;
    var argu=document.getElementById('argsname').value;
    var ret=document.getElementById('returnedvar').value;
    if (UI.python_mode){
      UI.insert(UI.focused,'def '+fc+'('+argu+'):');
      UI.indentline(UI.focused);
      if (loc.length!=0){
	UI.insert(UI.focused,'\n# local '+loc);
	UI.indentline(UI.focused);
	UI.insert(UI.focused,'\n\nreturn '+ret);
	UI.indentline(UI.focused);
	UI.moveCaretUpDown(UI.focused,-1);
	UI.indentline(UI.focused);
      }
      else {
	UI.insert(UI.focused,'\nreturn '+ret);
	UI.indentline(UI.focused);
      }
    }
    else {
      if (loc.length==0)
	UI.insert(UI.focused,fc+'('+argu+'):='+ret+';');
      else {
	UI.insert(UI.focused,'fonction '+fc+'('+argu+')\n  local '+loc+';\n  \n  retourne '+ret+';\nffonction:;\n');
	UI.moveCaretUpDown(UI.focused,-3);
	UI.moveCaret(UI.focused,2);
      }
    }
    document.getElementById('assistant_prog').style.display='none';
    UI.focused.focus();
  },
  assistant_seq_ok:function(){UI.focused=UI.savefocused;var tmp='seq('+document.getElementById('seqexpr').value+','+document.getElementById('seqvarname').value+','+document.getElementById('seqvarmin').value+','+document.getElementById('seqvarmax').value; UI.insert(UI.focused,tmp);tmp=document.getElementById('seqvarstep').value; if(tmp.length) UI.insert(UI.focused,','+tmp); UI.insert(UI.focused,')');document.getElementById('assistant_seq').style.display='none';},
  assistant_plot_polar:function(){UI.focused=UI.savefocused;var tmp='plotpolar('+document.getElementById('plotpolarexpr').value+','+document.getElementById('plotpolarvarname').value+','+document.getElementById('plotpolarvarmin').value+','+document.getElementById('plotpolarvarmax').value; UI.insert(UI.focused,tmp);tmp=document.getElementById('plotpolarvarstep').value; if(tmp.length) UI.insert(UI.focused,',tstep='+tmp); UI.insert(UI.focused,')');document.getElementById('assistant_plotpolar').style.display='none';},
  assistant_series_ok:function(){UI.focused=UI.savefocused;var tmp='series('+document.getElementById('seriesexpr').value+','+document.getElementById('seriesvarname').value+'='+document.getElementById('seriesvarlim').value+','+document.getElementById('seriesvarorder').value; UI.insert(UI.focused,tmp);tmp=document.getElementById('seriesvarstep').value; if(tmp.length) UI.insert(UI.focused,','+tmp); UI.insert(UI.focused,')');document.getElementById('assistant_series').style.display='none';},
  assistant_limit_ok:function(){UI.focused=UI.savefocused;var tmp='limit('+document.getElementById('limitexpr').value+','+document.getElementById('limitvarname').value+','+document.getElementById('limitvarlim').value; UI.insert(UI.focused,tmp);tmp=document.getElementById('limitvardir').value; if(tmp.length) UI.insert(UI.focused,','+tmp); UI.insert(UI.focused,')');document.getElementById('assistant_limit').style.display='none';},
  assistant_int_ok:function(){UI.focused=UI.savefocused;var tmp=document.getElementById('intexpr').value;if (tmp.length){ tmp='integrate('+tmp+','+document.getElementById('intvarname').value; UI.insert(UI.focused,tmp);tmp=document.getElementById('intvarmin').value; if(tmp.length) UI.insert(UI.focused,','+tmp+','+document.getElementById('intvarmax').value); UI.insert(UI.focused,')');}else UI.insert(UI.focused,'integrate(');document.getElementById('assistant_int').style.display='none';},
  assistant_diff_ok:function(){UI.focused=UI.savefocused;var tmp=document.getElementById('diffexpr').value;if (tmp.length){ tmp='diff('+tmp+','+document.getElementById('diffvarname').value; UI.insert(UI.focused,tmp);tmp=document.getElementById('diffnumber').value; if(tmp.length) UI.insert(UI.focused,','+tmp); UI.insert(UI.focused,')');}else UI.insert(UI.focused,'diff(');document.getElementById('assistant_diff').style.display='none';},
  assistant_sum_ok:function(){UI.focused=UI.savefocused;var tmp=document.getElementById('sumexpr').value;if (tmp.length){ tmp='sum('+tmp+','+document.getElementById('sumvarname').value; UI.insert(UI.focused,tmp);tmp=document.getElementById('sumvarmin').value; if(tmp.length) UI.insert(UI.focused,','+tmp+','+document.getElementById('sumvarmax').value); UI.insert(UI.focused,')');}else UI.insert(UI.focused,'sum(');document.getElementById('assistant_sum').style.display='none';},
  assistant_tabvarfunc_ok:function(){UI.focused=UI.savefocused;document.getElementById('assistant_tabvar').style.display='none';document.getElementById('assistant_tabvarfunc').style.display='none'; var tmp=document.getElementById('tabvarfuncname').value;if (tmp.length){tmp+=':='+document.getElementById('tabvarfuncvarname').value+'->'+document.getElementById('tabvarfuncexpr').value+';\n';tmp=tmp+'tabvar('+document.getElementById('tabvarfuncname').value+'('+document.getElementById('tabvarfuncvarname').value+'),';}else{tmp=tmp+'tabvar('+document.getElementById('tabvarfuncexpr').value+','} tmp+=document.getElementById('tabvarfuncvarname').value+','+document.getElementById('tabvarfuncvarmin').value+','+document.getElementById('tabvarfuncvarmax').value;var tmp1=document.getElementById('tabvarfuncopt').value; if(tmp1.length) tmp+=','+tmp1; tmp1=document.getElementById('tabvarfuncvarstep').value; if(tmp1.length) tmp=tmp+',xstep='+tmp1; tmp+=',plot)';UI.insert(UI.focused,tmp);},
  assistant_tabvarparam_ok:function(){UI.focused=UI.savefocused;document.getElementById('assistant_tabvar').style.display='none'; document.getElementById('assistant_tabvarparam').style.display='none'; var varname=document.getElementById('tabvarparamvarname').value; var exprx=document.getElementById('tabvarparamexprx').value ; var expry=document.getElementById('tabvarparamexpry').value ;var tmp=document.getElementById('tabvarparamnamex').value;if (tmp.length) tmp=tmp+':='+varname+'->'+exprx+';\n'+document.getElementById('tabvarparamnamey').value+':='+varname+'->'+expry+';\n';tmp=tmp+'tabvar(['+exprx+','+expry+'],'+varname+'='+document.getElementById('tabvarparamvarmin').value+'..'+document.getElementById('tabvarparamvarmax').value;var tmp1=document.getElementById('tabvarparamvarstep').value; if(tmp1.length) tmp=tmp+',tstep='+tmp1; tmp+=',plot)';UI.insert(UI.focused,tmp);},
  assistant_plotfunc1var_ok:function(){UI.focused=UI.savefocused;document.getElementById('assistant_plotfunc').style.display='none'; document.getElementById('assistant_plotfunc1var').style.display='none'; var tmp='plotfunc('+document.getElementById('plotfuncexpr').value+','+document.getElementById('plotfuncvarname').value+','+document.getElementById('plotfuncvarmin').value+','+document.getElementById('plotfuncvarmax').value;var tmp1=document.getElementById('plotfuncvarstep').value; if(tmp1.length) tmp=tmp+',xstep='+tmp1; tmp+=')';UI.insert(UI.focused,tmp);},
  assistant_plotfunc2var_ok:function(){UI.focused=UI.savefocused;document.getElementById('assistant_plotfunc').style.display='none'; document.getElementById('assistant_plotfunc2var').style.display='none'; var tmp='plotfunc('+document.getElementById('plotfunc2expr').value+',['+document.getElementById('plotfunc2varx').value+','+document.getElementById('plotfunc2vary').value+']';var tmp1=document.getElementById('plotfunc2varxstep').value; if(tmp1.length) tmp=tmp+',xstep='+tmp1;tmp1=document.getElementById('plotfunc2varystep').value; if(tmp1.length) tmp=tmp+',ystep='+tmp1; tmp+=')';UI.insert(UI.focused,tmp);},
  assistant_plotparam_ok:function(){UI.focused=UI.savefocused;document.getElementById('assistant_plotparam').style.display='none';document.getElementById('assistant_plotparam1var').style.display='none'; var tmp='plotparam(['+document.getElementById('plotparamexprx').value+','+document.getElementById('plotparamexpry').value+'],'+document.getElementById('plotparamvarname').value+','+document.getElementById('plotparamvarmin').value+','+document.getElementById('plotparamvarmax').value;var tmp1=document.getElementById('plotparamvarstep').value; if(tmp1.length) tmp=tmp+',tstep='+tmp1; tmp+=',display=cap_flat_line)';UI.insert(UI.focused,tmp);},
  assistant_plotparam2var_ok:function(){UI.focused=UI.savefocused;document.getElementById('assistant_plotparam').style.display='none';document.getElementById('assistant_plotparam2var').style.display='none'; var tmp='plotparam(['+document.getElementById('plotparam2exprx').value+','+document.getElementById('plotparam2expry').value+','+document.getElementById('plotparam2exprz').value+'],['+document.getElementById('plotparam2varx').value+','+document.getElementById('plotparam2vary').value+']';var tmp1=document.getElementById('plotparam2varxstep').value; if(tmp1.length) tmp=tmp+',ustep='+tmp1;tmp1=document.getElementById('plotparam2varystep').value; if(tmp1.length) tmp=tmp+',vstep='+tmp1; tmp+=')';UI.insert(UI.focused,tmp);},
  assistant_plotimplicit_ok:function(){UI.focused=UI.savefocused;document.getElementById('assistant_plotimplicit').style.display='none'; var ctr=document.getElementById('plotimplicitlevel').value; var tmp=document.getElementById('plotimplicitexprf').value+',['+document.getElementById('plotimplicitvarx').value+','+document.getElementById('plotimplicitvary').value+']'; if(ctr.length) tmp='plotcontour('+tmp+','+ctr; else tmp='plotimplicit('+tmp; var tmp1=document.getElementById('plotimplicitvarxstep').value; if(tmp1.length) tmp=tmp+',xstep='+tmp1;tmp1=document.getElementById('plotimplicitvarystep').value; if(tmp1.length) tmp=tmp+',ystep='+tmp1; tmp+=')';UI.insert(UI.focused,tmp);},
  assistant_plotfield_ok:function(){UI.focused=UI.savefocused;document.getElementById('assistant_plotfield').style.display='none'; var ctr=document.getElementById('plotfieldinit').value; var tmp=document.getElementById('plotfieldexprf').value+',['+document.getElementById('plotfieldvarx').value+','+document.getElementById('plotfieldvary').value+']'; if(ctr.length) tmp='plotfield('+tmp+',plotode='+ctr; else tmp='plotfield('+tmp; var tmp1=document.getElementById('plotfieldvarxstep').value; if(tmp1.length) tmp=tmp+',xstep='+tmp1;tmp1=document.getElementById('plotfieldvarystep').value; if(tmp1.length) tmp=tmp+',ystep='+tmp1; tmp+=')';UI.insert(UI.focused,tmp);},
  assistant_plotpolar_ok:function(){UI.focused=UI.savefocused;var tmp='plotpolar('+document.getElementById('plotpolarexpr').value+','+document.getElementById('plotpolarvarname').value+','+document.getElementById('plotpolarvarmin').value+','+document.getElementById('plotpolarvarmax').value; UI.insert(UI.focused,tmp);tmp=document.getElementById('plotpolarvarstep').value; if(tmp.length) UI.insert(UI.focused,',tstep='+tmp); UI.insert(UI.focused,')');document.getElementById('assistant_plotpolar').style.display='none';},
  assistant_rand_setdisplay:function(){
    var form=document.getElementById('assistant_rand');
    if (form.rand_int.checked){
      document.getElementById('chooselawdiv').style.display='none';
      document.getElementById('rand_intdiv').style.display='block';
    } else {
      document.getElementById('chooselawdiv').style.display='block';
      document.getElementById('law_arg').style.display='none';
      document.getElementById('rand_intdiv').style.display='none';
    }
  },
  assistant_matr_maxrows:40,
  assistant_matr_maxcols:6,
  assistant_matr_textarea:-1,
  assistant_matr_source:[], // JS array for spreadsheet, if length==0 matrix
  is_sheet:true,
  sheet_i:0,
  sheet_j:0,
  open_sheet:function(tableur){
    UI.funcoff();UI.savefocused=UI.focused;
    document.getElementById('assistant_matr').style.display='block';
    document.getElementById('matr_type_chooser').style.display='inline';
    document.getElementById('matr_stats').style.display='none';
    UI.assistant_matr_setdisplay();
    UI.is_sheet=tableur;
    document.getElementById('matr_or_sheet').checked=tableur;
    document.getElementById('matr_type_chooser').style.display=tableur?'none':'inline';
    if (tableur){
      document.getElementById('assistant_matr').matr_formuleshadow.checked=true;
      document.getElementById('assistant_matr').matr_formule.checked=false;
    }
    UI.assistant_matr_setdisplay();
    if (tableur) UI.matrix2spreadsheet(); else UI.spreadsheet2matrix(false);
    var field=document.getElementById('matr_span0_0');
    UI.sheet_onfocus(field); 
    //UI.set_focus('matr_span0_0');
  },
  sheet_rowadd:function(n){
    var field=document.getElementById('matr_nrows');
    field.value=eval(field.value)+n;
    var f=document.getElementById('stat_lmax');
    f.value++;
    UI.assistant_matr_setdisplay();
  },
  sheet_coladd:function(n){
    var field=document.getElementById('matr_ncols');
    field.value=eval(field.value)+n;
    UI.assistant_matr_setdisplay();
  },
  sheet_edit_cmd:function(cmd){
    var s=UI.focused.id;
    var sh=UI.is_sheet;
    if (!sh){ UI.is_sheet=true; UI.matrix2spreadsheet(); }
    if (s===undefined) return;
    if (s.length<12 || s.substr(0,9)!='matr_case') return;
    var l=s.length,i,j,err;
    for (i=8;i<l;++i){ if (s[i]=='_') break; }
    j=eval(s.substr(i+1,l-i-1));
    i=eval(s.substr(9,i-9));
    s=cmd+','+i+','+j;
    //console.log(s);
    UI.sheet_recompute(s);
    if (!sh){ UI.is_sheet=false; UI.spreadsheet2matrix(false); }
    if (cmd==2) UI.sheet_rowadd(1);
    if (cmd==3) UI.sheet_rowadd(-1);
    if (cmd==4) UI.sheet_coladd(1);
    if (cmd==5) UI.sheet_coladd(-1);
  },
  sheet_recompute:function(cmd){
    // if cmd=='' convert to CAS sheet, eval and convert back
    // else calls convert(matrix,cmd), where cmd='command,row,col',
    // command=0 copy down, =1 copy right
    // console.log('sheet_recompute',cmd);
    var R=UI.assistant_matr_maxrows;
    if (!UI.is_sheet || R==0) return;
    var s='spreadsheet[';
    for (var i=0;i<R;i++){
      var C=UI.assistant_matr_maxcols;
      s += '[';
      for (var j=0;j<C;j++){
	var field=document.getElementById('matr_case'+i+'_'+j);
	var tmp='['+field.value;
	if (tmp.length==1) tmp += '""';
	s += tmp+',0,0],';
      }
      s +='],';
    }
    s += ']';
    if (cmd.length!=0)
      s='convert('+s+',cell,'+cmd+')';
    //console.log(s);
    s=UI.caseval_noautosimp(s);
    if (s==' Clic_on_Exec ') return;
    //console.log(s);
    s=eval(s);
    UI.assistant_matr_source=s;
    //console.log(s);
    if (R>s.length) R=s.length;
    // dispatch to UI
    for (var i=0;i<R;i++){
      var r=s[i];
      var C=r.length;
      if (C>UI.assistant_matr_maxcols) C=UI.assistant_matr_maxcols;
      for (var j=0;j<C;j++){
	var field=document.getElementById('matr_span'+i+'_'+j);
	var field2=document.getElementById('matr_case'+i+'_'+j);
	//console.log(i,j,field,r);
	var tmp=r[j],tmp2;
	if (tmp === undefined) continue;
	if (r[j].length>1) {tmp2=tmp[0]; tmp=tmp[1]; } else tmp2=tmp=tmp[0];
	if (r[j].length==3) tmp=r[j][2];
	// console.log(i,j,tmp);
	if (tmp=='""') tmp='&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
	field.innerHTML=tmp;
	if (tmp2=='""') tmp2='';
	field2.value=tmp2;
	//console.log(i,j,tmp,field.innerHTML);
	// field.style.display='inline';
      }
    }
    return 1;
  },
  matrix2spreadsheet:function(){
    // convert matrix headers to spreadsheet and store source formulae
    var l=UI.assistant_matr_maxrows;
    var c=UI.assistant_matr_maxcols;
    //console.log(l,c);
    if (c>26){ UI.assistant_matr_maxcols=c=26; }
    for (var j=0;j<c;j++){
      document.getElementById('matr_head_'+j).innerHTML=String.fromCharCode(65+j);
    }
    UI.is_sheet=true;
    UI.sheet_recompute('');
    for (var i=0;i<l;i++){
      for (var j=0;j<c;j++){
	//console.log(i,j);
	var field=document.getElementById('matr_span'+i+'_'+j);
	field.style.display='inline';
	field.previousSibling.style.display='none';
      }
    }
  },
  spreadsheet2matrix:function(evaled){
    var l=UI.assistant_matr_maxrows;
    var c=UI.assistant_matr_maxcols;
    if (c>26){ UI.assistant_matr_maxcols=c=26; }
    for (var j=0;j<c;j++){
      document.getElementById('matr_head_'+j).innerHTML=''+j;
    }
    for (var i=0;i<l;i++){
      ligne=UI.assistant_matr_source[i];
      for (var j=0;j<c;j++){
	var tmp=ligne[j][1];
	if (tmp=='""') tmp='';
	var field=document.getElementById('matr_case'+i+'_'+j);
	if (evaled) field.value=tmp;
	field.style.display='inline';
	field.nextSibling.style.display='none';
      }
    }
    UI.is_sheet=false;
  },
  sheet_onfocus:function(field){
    //console.log(field.id,field.previousSibling.id);
    s=field.id;
    var l=s.length,i,j,err;
    for (i=8;i<l;++i){ if (s[i]=='_') break; }
    j=eval(s.substr(i+1,l-i-1));
    i=eval(s.substr(9,i-9));
    document.getElementById('matr_line_'+UI.sheet_i).style.color="black";
    document.getElementById('matr_head_'+UI.sheet_j).style.color="black";
    UI.sheet_i=i; UI.sheet_j=j;
    document.getElementById('matr_line_'+UI.sheet_i).style.color="red";
    document.getElementById('matr_head_'+UI.sheet_j).style.color="red";
    field=field.previousSibling;
    field.style.display='inline';
    field.focus();
    UI.focused=field;
  },
  sheet_set:function(field,value){
    field.value=value;
    var s=field.id;
    if (s.length>9 && s.substr(0,9)=='matr_case')
      document.getElementById('matr_span'+s.substr(9,s.length-9)).innerHTML=value;
  },
  assistant_matr_setmatrix:function(l,c){
    // Code de creation de la matrice
    if (l*c>10000){ l=100; c=100;}
    var mydiv=document.getElementById('matr_casediv');
    mydiv.style.maxHeight=window.innerHeight/2+'px';
    mydiv.style.maxWidth=(window.innerWidth-50)+'px';
    mydiv.style.overflow="auto";
    UI.assistant_matr_maxrows=l;
    UI.assistant_matr_maxcols=c;
    var s='<table>\n';
    var h = '<tr><th id="matr_head">@</th>';
    for (var j=0;j<c;++j){
      h+='<th id="matr_head_'+j+'" style="text-align:center">'+j+'</th>';
    }
    h += '</tr>\n';
    s += h;
    for (var i=0;i<l;++i){
      s += '<tr id="matr_ligne'+i+'">';
      s += '<td id="matr_line_'+i+'">'+i+'</td>';
      for (var j=0;j<c;++j){
	var field=document.getElementById('matr_case'+i+'_'+j);
	var oldval='';
	//console.log(i,j,field.value);
	if (field!==null) oldval=field.value;
	if (UI.assistant_matr_textarea>0)
	  s+='<td class="matrixcell"><textarea class="matrixcell" \
onkeypress="if (event.keyCode!=13) return true; UI.cb_matr_enter(this,true); return false;" \
onclick="UI.focused=this;" onblur="UI.sheet_blur(this)" onfocus="nextSibling.style.display=\'none\';UI.focused=this;" \
id="matr_case'+i+'_'+j+'">'+oldval+'</textarea><div class="matrixcell" style="display:none;width:20px" onclick="UI.sheet_onfocus(this);" id="matr_span'+i+'_'+j+'"></div></td>';
	else
	  s+='<td class="matrixcell" onclick="UI.sheet_onfocus(lastChild);"><input class="matrixcell" onkeypress="if (event.keyCode!=13) return true; UI.cb_matr_enter(this,true); return false;" onclick="UI.focused=this;" onblur="UI.sheet_blur(this)" onfocus="nextSibling.style.display=\'none\';UI.focused=this;" id="matr_case'+i+'_'+j+'" value="'+oldval+'" /><div class="matrixcell" style="display:none;width:20px" onclick="UI.sheet_onfocus(this);"  id="matr_span'+i+'_'+j+'"></div></td>';
      }
      s += '</tr>\n';
    }
    s += '</table>';
    //console.log(s);
    mydiv.innerHTML=s;
    if (document.getElementById('matr_or_sheet').checked){ UI.matrix2spreadsheet();}
    //console.log(mydiv.innerHTML);
    //mydiv.style.display='none';
  },
  sheet_blur:function(field){
    UI.cb_matr_enter(field,false); 
    //console.log(field.innerHTML);
    //console.log(field.nextSibling.innerHTML);
    field.style.display='none'; field.nextSibling.style.display='inline';
  },
  cb_matr_enter:function(field,focusnext){
    var s='csv2gen("'+field.value+'",string)';
    //console.log(s);
    var se=UI.caseval_noautosimp(s);
    if (se.length>8 && se.substr(0,8)=='matrix[[')
      se=se.substr(6,se.length-6);
    //console.log(se);
    s=field.id;
    var l=s.length,i,j,err;
    for (i=8;i<l;++i){ if (s[i]=='_') break; }
    j=eval(s.substr(i+1,l-i-1));
    i=eval(s.substr(9,i-9));
    var form=document.getElementById('assistant_matr'),nr=form.matr_nrows.value,nc=form.matr_ncols.value;
    try { se=eval(se); } catch(err){ se=UI.caseval_noautosimp(field.value); }
    // console.log(i,j); // position dans la matrice
    if (!Array.isArray(se)){
      //console.log(i,j,field.id); // position dans la matrice
      UI.sheet_set(field,se);
      i++;
      if (i>=nr){
	i=0; j++; if (j>=nc) j=0; 
      }
      UI.sheet_recompute('');
      var tmp='matr_span'+i+'_'+j; // console.log(tmp);
      if (focusnext) document.getElementById(tmp).click();
      return;
    }
    else {
      l=se.length;
      if (l==0) return;
      var cell=se[0];
      if (Array.isArray(cell)){
	// remplissage style matrice
	var iend=i+l,j0=j,ishift=i,extend=false;
	if (iend>=UI.assistant_matr_maxnrows) iend=UI.assistant_matr_maxnrows;
	if (iend>form.matr_nrows.value){ extend=true; form.matr_nrows.value=iend;}
	for (;i<iend;++i){
	  var ligne=se[i-ishift];
	  if (Array.isArray(ligne)){
	    var j_=j,jend=j+ligne.length;
	    if (jend>=UI.assistant_matr_maxncols) jend=UI.assistant_matr_maxncols;
	    if (jend>form.matr_ncols.value){ extend=true;  form.matr_ncols.value=jend; }
	    for (;j_<jend;++j_) UI.sheet_set(document.getElementById('matr_case'+i+'_'+j_),ligne[j_-j]);
	  }
	  else
	    UI.sheet_set(document.getElementById('matr_case'+i+'_'+j),ligne);
	}
	if (extend){
	  UI.assistant_matr_setdisplay();
	  UI.sheet_recompute('');
	}
	else {
	  //console.log(iend,j0);
	  if (iend>=nr) iend=0; if (j0>=nc) j0=0;
	  UI.sheet_recompute('');
	  tmp='matr_span'+iend+'_'+j0;
	  if (focusnext) document.getElementById(tmp).click();
	}
	return;
      }
      // remplissage ligne i, colonnes j -> j+l-1
      var jend=j+l,shift=j;
      if (jend>=UI.assistant_matr_maxncols) jend=UI.assistant_matr_maxncols;
      for (;j<jend;++j)
	UI.sheet_set(document.getElementById('matr_case'+i+'_'+j),se[j-shift]);
      UI.sheet_recompute('');
    }
  },
  adequation:function(form){
    var test;
    for (test=0;test<7;++test){
      if (form.adequation[test].checked) break;
    }
    //console.log(test);
    if (test==0 || test==1){
      document.getElementById('matr').style.display='none';
      document.getElementById('matr_matr').style.display='none';
    }
    else {
      document.getElementById('matr').style.display='block';
      document.getElementById('matr_matr').style.display='block';
    }
  },
  assistant_rand_ok:function(){
    document.getElementById('assistant_rand').style.display='none';
    document.getElementById('chooselawdiv').style.display='none';
    UI.focused=UI.savefocused;
    var nr=document.getElementById('rand_nrows').value;
    var nc=document.getElementById('rand_ncols').value,tmp;
    if (nc<=0)
      tmp='rand(';
    else {
      if (nr<=0)
	tmp='ranv('+nc+',';
      else
	tmp='ranm('+nr+','+nc+',';
    }
    var form=document.getElementById('assistant_rand');
    var entier=form.rand_int.checked;
    if (entier){
      var nm=document.getElementById('rand_maxint').value;
      tmp += nm+')';
    }
    else {
      form=document.getElementById('chooselawform');
      tmp += form.rand_law.value;
      if (form.rand_law1.style.display!='none')
	tmp += ','+form.rand_law1.value;
      if (form.rand_law2.style.display!='none')
	tmp += ','+form.rand_law2.value;
      tmp += ')';
    }
    //console.log(tmp);
    UI.insert(UI.focused,tmp);
  },
  assistant_matr_ok:function(){
    var stats=document.getElementById('matr_stats').style.display!='none';
    var stat12=document.getElementById('matr_stat12').style.display!='none';
    var stathyp=document.getElementById('matr_testhyp').style.display!='none';
    var fluctu=document.getElementById('risque_alpha').style.display!='none';
    document.getElementById('assistant_matr').style.display='none';
    document.getElementById('chooselawdiv').style.display='none';
    document.getElementById('risque_alpha').style.display='none';
    UI.focused=UI.savefocused;
    var tmp; 
    if (stats && !stat12 && !stathyp){
      var form=document.getElementById('chooselawform');
      tmp=form.rand_law.value;
      if (fluctu) tmp +='_icdf';
      tmp += '(';
      if (form.rand_law1.style.display!='none')
	tmp += form.rand_law1.value+',';
      if (form.rand_law2.style.display!='none')
	tmp += form.rand_law2.value+',';
      if (fluctu){
	var alpha=0.05;
	var alphaf=document.getElementById('adequation_alpha');
	//console.log(alphaf.value); return;
	if (alphaf.value.length) alpha=eval(alphaf.value);
	tmp = tmp+alpha/2+'),\n'+tmp+(1-alpha/2)+');';
      }
      else {
	var argu=document.getElementById('law_arg');
	tmp += argu.value+')';
      }
      UI.insert(UI.focused,tmp);
      return;
    }
    var form=document.getElementById('assistant_matr');
    var mat=form.matr_name.value;
    if (stats && mat.length==0) mat='m_s';
    var nrows=document.getElementById('matr_nrows');
    var ncols=document.getElementById('matr_ncols');
    var maxrows=40,maxcols=6;
    if (ncols.value>maxcols) ncols.value=maxcols;
    if (nrows.value>maxrows) nrows.value=maxrows;
    if (mat.length) tmp=mat+':=';
    if (form.matr_formule.checked){
      tmp+='matrix('+nrows.value+','+ncols.value+',';
      tmp+='(j,k)->';
      var expr=document.getElementById('matr_expr').value;
      //console.log(expr);
      if (!form.matr_start0.checked) expr=UI.caseval('subst('+expr+',[j,k],[j+1,k+1])');
      tmp += expr;
      tmp +=')';
    }
    else {
      tmp += '[';
      for (var i=0;i<nrows.value;i++){
	tmp += '[';
	for (var j=0;j<ncols.value;j++){
	  //console.log(j,tmp);
	  var val=document.getElementById('matr_case'+i+'_'+j).value;
	  if (UI.is_sheet && i<UI.assistant_matr_source.length){
	    var ligne=UI.assistant_matr_source[i];
	    if (j<ligne.length){
	      ligne=ligne[j];
	      if (ligne.length>1){
		ligne=ligne[1];
		if (ligne!='""') val=ligne;
	      }
	    }
	  }
	  if (val.length>0) tmp+=val; else tmp+='0';
	  if (j<ncols.value-1) tmp+=',';
	}
	tmp += ']';
	if (i<nrows.value-1) tmp+=',\n';
      }
      tmp += ']'; 
    }
    if (stats){
      tmp += ':;\n';
      var submat=mat+'['+form.stat_lmin.value+'..'+form.stat_lmax.value+','+form.stat_cmin.value+'..'+form.stat_cmax.value+']';
      if (stat12){
	if (form.stat_mean.checked) tmp+='mean('+submat+');\n';
	if (form.stat_stddev.checked) tmp+='stddev('+submat+');\n';
	if (form.stat_quartiles.checked) tmp+='quartiles('+submat+');\n';
	if (form.stat_histo.checked) tmp+='histogram('+submat+',0,1);\n';
	if (form.stat_moustache.checked) tmp+='moustache('+submat+');\n';
	if (form.stat_scatter.checked) tmp+='scatterplot('+submat+');\n';
	if (form.stat_polygonscatter.checked) tmp+='polygonscatterplot('+submat+');\n';
	if (form.stat_linreg.checked) tmp+='linear_regression_plot('+submat+');\n';    
      }
      else {
	var alpha=0.05,test,hyp,mu=form.adequation_mu.value,sigma=0,dof=1;
	if (form.adequation_alpha.value.length)
	  alpha=form.adequation_alpha.value;
	if (form.adequation_sigma.value.length)
	  sigma=form.adequation_sigma.value;
	for (test=0;test<7;++test){
	  if (form.adequation[test].checked) break;
	}
	for (hyp=0;hyp<3;++hyp){
	  if (form.adequation_alt[hyp].checked) break;
	}
	if (test==3) tmp += 'chisquaret(';
	if (test==4) tmp += 'kolmogorovt(';
	if (test==5) tmp += 'wilcoxont(';
	var l1=form.stat_lmin.value,l2=form.stat_lmax.value,
	    c1=form.stat_cmin.value,c2=form.stat_cmax.value;
	if (test>=3 && test<=5){
	  if (l2-l1>c2-c1){ // lines
	    tmp += mat+'['+l1+'..'+l2+','+c1+'],';
	    tmp += mat+'['+l1+'..'+l2+','+c2+']';
	    dof=l2-l1;
	  }
	  else {
	    tmp += mat+'['+l1+','+c1+'..'+c2+'],';
	    tmp += mat+'['+l2+','+c1+'..'+c2+']';
	    dof=c2-c1;
	  }
	  if (test==5){
	    if (hyp==0) tmp += ',\'<\'';
	    if (hyp==1) tmp += ',\'!=\'';
	    if (hyp==2) tmp += ',\'>\'';
	    tmp += ','+alpha;
	  }
	  tmp += ');';
	}
	if (test==3) tmp += 'chisquare_icdf('+dof+','+(1-alpha)+');';
	if (test==6) tmp += 'normalt(';
	if (test==7) tmp += 'studentt(';
	if (test==0){
	  var n=form.confiance_n.value,p=form.confiance_p.value;
	  var coeff='1/2';
	  if (n>100) coeff='sqrt('+(n/(n-1)*p*(1-p))+')';
	  tmp='p:='+p+';n:='+n+';alpha:='+alpha+';\ndelta_p:='+coeff+'*normald_icdf(0,1,(1-alpha/2))/sqrt(n);';
	  tmp +='\n[p-delta_p,p+delta_p];\n';
	  if (n*p<5 || n*(1-p)<5) tmp="Erreur : n*p et n*(1-p) doivent etre plus grand que 5"; 
	  UI.insert(UI.focused,tmp);
	  return;
	}
	if (test==1){
	  var n=form.confiance_n_.value,mu=form.confiance_mu.value,sigma=form.confiance_sigma.value;
	  tmp = 'mu:='+mu+'; sigma:='+sigma+';\n';
	  tmp += 'delta:=sigma/sqrt('+n+')*student_icdf('+n+','+(1-alpha/2)+');\n';
	  tmp += '[mu-delta,mu+delta]';
	}
	if (test==2){
	  tmp += 'mu:=mean(flatten('+submat+'));\n'
	  dof=(c2-c1+1)*(l2-l1+1)-1;
	  tmp += 'delta:=stddevp(flatten('+submat+'))/sqrt('+dof+')*student_icdf('+dof+','+(1-alpha/2)+');\n';
	  tmp += '[mu-delta,mu+delta]';
	}
	if (test==6 || test==7){
	  tmp += 'flatten('+submat+'),'+mu+',';
	  if (sigma>0)
	    tmp += sigma+',';
	  if (hyp==0) tmp += '\'<\'';
	  if (hyp==1) tmp += '\'!=\'';
	  if (hyp==2) tmp += '\'>\'';
	  tmp += ','+alpha+')';
	}
      }
    }
    //console.log(tmp);
    UI.insert(UI.focused,tmp);
  },
  assistant_matr_setdisplay:function(){
    document.getElementById('matr_matr').style.display='block';
    document.getElementById('chooselawdiv').style.display='none';
    var form=document.getElementById('assistant_matr');
    if (form.matr_nrows.value<0) form.matr_nrows.value=0;
    if (form.matr_ncols.value<0) form.matr_ncols.value=0;
    if (document.getElementById('matr_stats').style.display!='none'){
      if (form.matr_nrows.value<1) form.matr_nrows.value=1;
      if (form.matr_ncols.value<1) form.matr_ncols.value=1;
      if (form.stat_lmax.value>=form.matr_nrows.value)
	form.stat_lmax.value=form.matr_nrows.value-1;
      if (form.stat_lmin.value>=form.matr_nrows.value)
	form.stat_lmin.value=form.matr_nrows.value-1;
      form.stat_lmax.max=form.matr_nrows.value-1;
      form.stat_lmin.max=form.matr_nrows.value-1;
      if (form.stat_cmax.value>=form.matr_ncols.value)
	form.stat_cmax.value=form.matr_ncols.value-1;
      if (form.stat_cmin.value>=form.matr_ncols.value)
	form.stat_cmin.value=form.matr_ncols.value-1;
      form.stat_cmax.max=form.matr_ncols.value-1;
      form.stat_cmin.max=form.matr_ncols.value-1;
    }
    form.matr_ncols.max=UI.assistant_matr_maxncols;
    form.matr_nrows.max=UI.assistant_matr_maxnrows;
    if (form.matr_formule.checked){
      document.getElementById('matr_formulediv').style.display='inline';
      UI.set_focus('matr_expr');
      document.getElementById('matr').style.display='none';
    } else {
      document.getElementById('matr_formulediv').style.display='none';
      document.getElementById('matr').style.display='block';
      var nrows=document.getElementById('matr_nrows');
      var ncols=document.getElementById('matr_ncols');
      var maxrows=UI.assistant_matr_maxrows,maxcols=UI.assistant_matr_maxcols;
      //console.log(nrows.value,maxrows,ncols.value,maxcols);
      if (ncols.value<1) ncols.value=1;
      if (ncols.value>maxcols) ncols.value=maxcols;
      if (nrows.value<1) nrows.value=1;
      if (nrows.value>maxrows) nrows.value=maxrows;
      //console.log("matr",nrows.value,ncols.value);
      var matr=[];
      matr.length=maxrows;
      for (var j=0;j<maxcols;j++){
	var tmp=document.getElementById('matr_head_'+j);
	if (j<ncols.value) tmp.style.visibility='visible'; else tmp.style.visibility='hidden';
      }
      for (var i=0;i<maxrows;i++){
	//document.getElementById('matr_ligne'+i).style.visibility='hidden';
	document.getElementById('matr_ligne'+i).style.display='none';
	var ligne=[];
	ligne.length=maxcols;
	for (var j=0;j<maxcols;j++){
	  ligne[j]=document.getElementById('matr_case'+i+'_'+j);
	  ligne[j].style.display='none';
	  //console.log(j,ligne[j].parentNode.style.display);
	  ligne[j].parentNode.style.display='none';
	  ligne[j].nextSibling.style.display='none';
	}
	matr[i]=ligne;
      }
      for (var i=0;i<nrows.value;i++){
	//document.getElementById('matr_ligne'+i).style.visibility='visible';
	document.getElementById('matr_ligne'+i).style.display='table-row';
	if (UI.is_sheet){
	  for (var j=0;j<ncols.value;j++){
	    var f=matr[i][j];
	    // console.log(i,j,f.innerHTML);
	    f.nextSibling.style.display='inline';
	    f.parentNode.style.display='';
	  }
	}
	else {
	  for (var j=0;j<ncols.value;j++){
	    matr[i][j].style.display='inline';
	    matr[i][j].parentNode.style.display='';
	  }
	}
      }
      //UI.set_focus(matr[0][0]);
    }
  },
  toggleshift:function(){
    UI.kbdshift=!UI.kbdshift;
    if (UI.kbdshift){
      document.getElementById('shift_key').style.backgroundColor="white";
      document.getElementById('add_left_par').value="[";
      document.getElementById('add_right_par').value="]";
      document.getElementById('add_ln').value="ln";
      document.getElementById('add_sin').value="asin";
      document.getElementById('add_cos').value="acos";
      document.getElementById('add_tan').value="atan";
      document.getElementById('add_newline').value="\\n";
      document.getElementById('add_,').value="'";
      document.getElementById('add_:').value="!";
      document.getElementById('add_semi').value="\"";
      document.getElementById('add-=').value="_";
      // document.getElementById('add_infer').value=">";
      document.getElementById('add_sqrt').value="^2";
      document.getElementById('add_/').value="%";
      document.getElementById('add_pi').value="∞";
    }
    else {
      document.getElementById('shift_key').style.backgroundColor="cyan";
      document.getElementById('add_left_par').value="(";
      document.getElementById('add_right_par').value=")";
      document.getElementById('add_ln').value="exp";
      document.getElementById('add_sin').value="sin";
      document.getElementById('add_cos').value="cos";
      document.getElementById('add_tan').value="tan";
      document.getElementById('add_newline').value=" ";
      document.getElementById('add_,').value=",";
      document.getElementById('add_:').value=UI.python_mode?':':':=';
      document.getElementById('add_semi').value=";";
      document.getElementById('add-=').value="=";
      // document.getElementById('add_infer').value="<";
      document.getElementById('add_sqrt').value="√";
      document.getElementById('add_/').value="/";
      document.getElementById('add_pi').value="π";
    }
  },
  codemirror_setoptions:function(cmentree){
    UI.setoption_mode(cmentree);
    cmentree.setOption("extraKeys", {
      Enter: function(cm){
        //UI.set_editline(cmentree,false);
	UI.eval_cmdline();
      },
      "Ctrl-Enter": function(cm){
        //UI.set_editline(cmentree,false);
	UI.eval_cmdline();
      },
      Backspace: function(cm){
	UI.backspace(cm);
      },
      F1: function(cm) {
	UI.completion(cm);
      },
      Tab: function(cm) {
	UI.indentline(cm);
      },
    });
  },
  switchcm:function(){
    if (UI.usecm){
      if (cmentree==entree){
	// cmentree may be released with cmentree.toTextArea();
	cmentree=CodeMirror.fromTextArea(entree,{
	  matchBrackets: true,
	  lineNumbers: true,
	  viewportMargin: Infinity
	});
	UI.setoption_mode(cmentree);
	//console.log(entree.type);
	//cmentree.setSize(window.innerWidth-20,40);
	cmentree.options.indentUnit=UI.python_mode?UI.python_indent:2; 
	cmentree.on("focus",function(cm){ UI.set_focused(cm); UI.set_config_width();});
	cmentree.on("blur",function(cm) { if (cm.getSelection().length > 0){UI.selection=cm.getSelection();} });
	cmentree.setValue(entree.value);
	UI.changefontsize(cmentree,18);
	UI.codemirror_setoptions(cmentree);
      } // if (UI.usecm)
    } else { if (cmentree!=entree) cmentree.toTextArea(); cmentree=entree; }
    cmentree.focus();
  },
  setoption_mode:function(cmentree){
    if (!UI.usecm) return;
    if (UI.python_mode){
      //console.log('Python mode');
      cmentree.setOption("mode", "python");
    }
    else {
      //console.log('Xcas mode');
      cmentree.setOption("mode", "simplemode");
    }
  },
  kbdonfuncoff:function() {
    UI.savefocused=UI.focused;
    document.getElementById('keyboard').style.display='inline';
    document.getElementById('keyboardfunc').style.display='none';
  },
  funcoff:function() {
    UI.savefocused=UI.focused;
    document.getElementById('keyboardfunc').style.display='none';
  },
  restorefrom:function(c){
    var s=UI.readCookie(c);
    UI.restoresession(s,document.getElementById('mathoutput'),true,false);
    //console.log(c.substring(6,c.length));
    document.getElementById('outputfilename').value=c.substring(6,c.length);
    document.getElementById('loadfile_cookie').innerHTML='';
  },
  listCookies:function() { // list cookies with name begin == ' xcas__'
    var aString = '';
    if (window.localStorage){
      for(var i=0, len=localStorage.length; i<len; i++) {
	var tmp = localStorage.key(i);
	//console.log(tmp);
	if (tmp.substr(0,6)=='xcas__' ){
	  var tmpname=tmp.substr(6,tmp.length-6);
	  aString += "<button onclick=\"UI.restorefrom('"+tmp.substr(0,pos)+"')\">"+tmpname+"</button>\n";
	}
      }
    }
    var theCookies = document.cookie.split(';');
    for (var i = 0 ; i < theCookies.length; i++) {
      // console.log(i,theCookies[i].substr(0,7));
      var tmp=theCookies[i];
      var pos=tmp.search('=');
      if (pos>7 && tmp.substr(0,7)==' xcas__' ){
	var tmpname=tmp.substr(7,pos-7);
	aString += "<button onclick=\"UI.restorefrom('"+tmp.substr(1,pos-1)+"')\">"+tmpname+"</button>\n";
      }
    }
    aString += "<button onclick=document.getElementById('loadfile_cookie').innerHTML=''>&#x274C;</button>\n"
    //console.log(aString);
    return aString;
  },
  createCookie:function(name,value,days) {
    if (window.localStorage) return localStorage.setItem(name,value);
    if (days) {
      var date = new Date();
      date.setTime(date.getTime()+(days*24*60*60*1000));
      var expires = "; expires="+date.toGMTString();
    }
    else var expires = "";
    document.cookie = name+"="+value+expires+"; path=/";
  },
  readCookie:function(name) {
    if (window.localStorage){
      var tmp=localStorage.getItem(name);
      if (tmp!=null) return tmp;
    }
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
      var c = ca[i];
      while (c.charAt(0)==' ') c = c.substring(1,c.length);
      if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return null;
  },
  eraseCookie:function(name) {
    if (window.localStorage) return localStorage.removeItem(name);
    createCookie(name,"",-1);
  },
  detectmob:function() { 
    if( navigator.userAgent.match(/Android/i)
	|| navigator.userAgent.match(/webOS/i)
	|| navigator.userAgent.match(/iPhone/i)
	|| navigator.userAgent.match(/iPad/i)
	|| navigator.userAgent.match(/iPod/i)
	|| navigator.userAgent.match(/BlackBerry/i)
	|| navigator.userAgent.match(/Windows Phone/i)
      ) return true;
    else 
      return false;
  },
  browser_type: function(){
    var isOpera = !!window.opera || navigator.userAgent.indexOf(' OPR/') >= 0;
    var isFirefox = typeof InstallTrigger !== 'undefined';   // Firefox 1.0+
    var isSafari = Object.prototype.toString.call(window.HTMLElement).indexOf('Constructor') > 0;
    var isChrome = !!window.chrome && !isOpera;              // Chrome 1+
    var isIE = /*@cc_on!@*/false || !!document.documentMode; // At least IE6
    if (isFirefox) return 1;
    if (isSafari) return 2;
    if (isChrome) return 3;
    if (isIE) return 4;
    if (isOpera) return 5;
    return 0;
  },
  lowercase1: function(text){
    var value=text;
    if (value.length && value.charCodeAt(0)>64 && value.charCodeAt(0)<90)
      value = value.substr(0,1).toLowerCase()+value.substr(1,value.length-1);
    return value;
  },
  caseval: function(text){
    if (!UI.ready) return ' Clic_on_Exec ';
    var docaseval = Module.cwrap('caseval',  'string', ['string']);
    var value=text;
    value=value.replace(/%22/g,'\"'); 
    var n=value.search(';');
    if (n<0 || n>=value.length)
      value='add_autosimplify('+value+')';
    var s,err;
    try {s=docaseval(value); } catch(err){ console.log(err); }
    // Module.print(text+ ' '+s);
    return s;
  },
  caseval_noautosimp: function(text){
    if (!UI.ready) return ' Clic_on_Exec ';
    var docaseval = Module.cwrap('caseval',  'string', ['string']);
    var value=text;
    value=value.replace(/%22/g,'\"'); 
    var s,err;
    try {s=docaseval(value); } catch(err){ console.log(err); }
    return s;
  },
  webworker:0,
  withworker:0,
  busy:0,
  casevalcb: function(text,callback,args){
    // prepare for webworker: casevalcb will run docaseval in a worker
    // 3d plotting does not work...
    if (UI.withworker && !!window.Worker) {
      if (!UI.webworker){
	UI.webworker = new Worker("giacworker.js");
	console.log('worker created ');
	UI.webworker.onmessage =  function(e){
	  var s=e.data[1];
	  if (e.data[0]=='cas') Module.print(s);
	  if (e.data[0]=='print') Module.print(s);
	}
      }
      // the worker will do the evaluation and post s
      UI.webworker.onmessage =  function(e){
	var s=e.data[1]; UI.busy=0;
	if (e.data[0]=='cas') callback(s,args);
	if (e.data[0]=='print') Module.print(s);
      }
      UI.busy=1;
      UI.webworker.postMessage(['eval',text]);
      return;
      // STOP: myWorker.terminate()
    }
    var docaseval = Module.cwrap('caseval',  'string', ['string']);
    var value=text;
    var n=value.search(';');
    if (n<0 || n>=value.length)
      value='add_autosimplify('+value+')';
    var s,err;
    try {s=docaseval(value); } catch(err){ }
    // Module.print(text+ ' '+s);
    return callback(s,args);
  },
  history_cm:0,
  ckenter: function(event,field){
    //console.log(event.keyCode,event.shiftKey);
    var key = event.keyCode;
    if (key==13 && event.shiftKey){UI.insert(field,'\n');  UI.indentline(field); return false;}
    if (key != 13 || event.shiftKey) return true;
    UI.reeval(field,'',true);
    return false;
  },
  ckenter_comment: function(event,field){
    //console.log(event.keyCode,event.shiftKey);
    var key = event.keyCode;
    if (key==13) UI.resizetextarea(field);
    var skipline=key != 13 || !event.ctrlKey;
    if (skipline && key==13 && !event.shiftKey){ // check enter at beginning of field
      var pos=field.selectionStart;
      var end=field.selectionEnd;
      if (pos==0 && end==0)
	skipline=false;
    }
    if (skipline) return true;
    UI.editcomment_end(field.nextSibling);
    var par=field.parentNode;
    par=par.parentNode;
    par=par.parentNode;
    par=par.parentNode.nextSibling;
    if (par==null) cmentree.focus(); 
    else {
      par=par.firstChild.firstChild.nextSibling.nextSibling;
      par=par.firstChild;
      if (par.style.display=='none'){ // commentaire
	par=par.nextSibling;
	par.click();
      }
      else
	par.focus();
    }
    return false;
  },
  restoresession: function(chaine,hist,asked,doexec){
    //console.log(chaine,doexec);
    var clearcmd=true;
    var hashParams=chaine.split('&');
    if (hashParams.length==0) return;
    for(var i = 0; i < hashParams.length; i++){
      var s = hashParams[i];
      if (s.length)  document.getElementById('startup_restore').style.display='none';
      if (s=='exec'){
	console.log(s);
	doexec=true;
	continue;
      }
      s=s.replace(/___/g,'%'); 
      s=decodeURIComponent(s); //console.log(s);
      // s=s.replace('%0a','\n','g');
      s=s.replace(/%3b/g,';'); 
      // s=s.replace('%3b',';','g'); 
      // s=s.replace('%3C','<','g'); 
      // s=s.replace('%3e','>','g');
      // s=s.replace('%5e','^','g');
      // s=s.replace('%20',' ','g');
      // s=s.replace('%27','\'','g');
      // s=s.replace('%22','\"','g');
      // s=s.replace('%C3%A9','é','g'); 
      // s=s.replace('%C3%A8','è','g'); 
      if (s.length && s.charAt(0)=='+'){
	s=s.substr(1);
	// if (!asked) doexec=true;
	if (s.length) UI.eval_cmdline1(s,false);
	continue;
      }
      if (s.length && s.charAt(0)=='*'){
	if (!asked) doexec=true;
	var pos=s.search(',');
	var name=s.substr(1,pos-1);
	// Module.print(name);
	s=s.substr(pos+1,s.length-pos-1);
	pos=s.search(',');
	var value=s.substr(0,pos);
	// Module.print(value);
	s=s.substr(pos+1,s.length-pos-1);
	pos=s.search(',');
	var mini=s.substr(0,pos);
	// Module.print(mini);
	s=s.substr(pos+1,s.length-pos-1);
	pos=s.search(',');
	var maxi=s.substr(0,pos);
	// Module.print(maxi);
	s=s.substr(pos+1,s.length-pos-1);
	UI.addcurseur(name,value,mini,maxi,s);
	continue;
      }
      var p = s.split('=');
      if (p[0]=='') continue;
      if (p[0]=='from'){
	UI.mailto=decodeURIComponent(p[1]);
	continue;
      }
      if (p[0]=='filename'){
	var out=document.getElementById("outputfilename");
	var s=decodeURIComponent(p[1]);
	out.value=s;
	//console.log(out);
	if (!UI.detectmob())
	  out.style.width=(s.length*10)+"px";
	continue;
      }
      if (p[0]=='entree' || p[0]=='cmentree'){
	cmentree.setValue( decodeURIComponent(p[1]));
	clearcmd=false;
	continue;
      }
      if (p[0]=='codemirror'){
	if (p[1]=='0') { document.getElementById('config').usecm.checked=false;  UI.set_config(false);}
	if (p[1]=='1') { document.getElementById('config').usecm.checked=true;  UI.set_config(false);}
	continue;
      }
      if (p[0]=='python'){
	var form=document.getElementById('config');
	if (p[1]=='0'){ form.python_mode.checked=false;}
	if (p[1]=='1'){ form.python_mode.checked=true;}
	UI.python_mode=form.python_mode.checked;
	UI.setoption_mode(cmentree);
	continue;
      }
      document.getElementById(p[0]).value = decodeURIComponent(p[1]);
    } // end for (i=...)
    if (doexec){ UI.exec(hist,0); }
    if (clearcmd && cmentree) cmentree.setValue('');
    if (hist.firstChild!=null) hist.firstChild.scrollIntoView();
  },
  link: function(start){
    var s=UI.makelink(start);
    //console.log(UI.from);
    UI.createCookie('xcas_session',s,365);
    if (s.length>0){
      var s2 = "#exec&"+s;
      var smail;
      if (UI.langue==-1)
	smail= UI.base_url+"xcasfr.html#exec&";
      else
	smail= UI.base_url+"xcasen.html#exec&";
      var filename=document.getElementById("outputfilename").value;
      var pos=filename.search('@');
      if (pos<0 || pos>=filename.length)
	filename=UI.from+'@'+filename;
      if (pos==0)
	filename=filename.substr(1,filename.length-1);
      filename='filename='+encodeURIComponent(filename)+'&';
      if (UI.from.length)
	filename+='from='+encodeURIComponent(UI.from)+'&';
      s=filename+s;
      smail=smail+s;
      if (UI.langue==-1)
	s = UI.base_url+"xcasfr.html#"+s;
      else
	s = UI.base_url+"xcasen.html#"+s;
      //Module.print(s);
      if (window.location.href.substr(0,4)=='file' && !UI.detectmob()){
	document.getElementById('thelink').innerHTML='<a href="'+s+'" target="_blank">x2</a>, <a href="'+s2+'" target="_blank">local</a>,';
      }
      else
	document.getElementById('thelink').innerHTML='<a href="'+s+'" target="_blank">x2</a>,';
      document.getElementById('themailto').innerHTML='<a href="mailto:'+UI.mailto+'?subject=session Xcas&body=Bonjour%0d%0aVeuillez suivre ce lien : <'+UI.rewritestring(smail)+'>">Mail</a>,<a href="#" target="_blank">&nbsp;+&nbsp;</a>';
    }
  },
  rewritestring: function(s){
    var res,i,l,ch;
    l=s.length; res='';
    for (i=0;i<l;++i){
      ch=s[i];
      if (ch=='&'){ res += "%26"; continue; }
      if (ch=='#'){ res += "%23"; continue; }
      if (i<l-2 && ch=='%' && s[i+1]!='7') { res += "___"; continue; }
      res += s[i];
    }
    return res;
  },
  makelink: function(start){
    var s='python=';
    if (UI.python_mode) s+='1&'; else s+='0&';
    var cur=document.getElementById('mathoutput').firstChild;
    var i=0;
    for (;cur;i++){
      if (i>=start){
	var field=cur.firstChild;
	field=field.firstChild;
	field=UI.skip_buttons(field);
	var fs=field.innerHTML;
	if (fs.length>6 && fs.substr(0,6)=="<span "){ // comment
	  fs=field.firstChild.firstChild.value;
	  fs=fs.replace(/\n/g,'%0a');
	  //console.log(fs);
	}
	if (fs.length>5){
	  var fs1=fs.substr(0,5);
	  if (fs1=="<form") {
	    var pos1=fs.search("<input");
	    fs=fs.substr(pos1,fs.length-pos1);
	    //console.log(fs);
	    var pos1=fs.search("value=");
	    pos1 += 7;
	    fs=fs.substr(pos1,fs.length-pos1);
	    var pos2=fs.search("\"");
	    fs1=fs.substr(0,pos2); // cursor name
	    var pos1=fs.search("value=");
	    pos1 += 7;
	    fs=fs.substr(pos1,fs.length-pos1);
	    var pos2=fs.search("\"");
	    fs1 += ','+fs.substr(0,pos2); // current value
	    var pos1=fs.search("minname"); 
	    pos1 += 7;
	    fs=fs.substr(pos1,fs.length-pos1);
	    var pos1=fs.search("value=");
	    pos1 += 7;
	    fs=fs.substr(pos1,fs.length-pos1);
	    var pos2=fs.search("\"");
	    fs1 += ','+fs.substr(0,pos2); // min
	    var pos1=fs.search("maxname");
	    pos1 += 7;
	    fs=fs.substr(pos1,fs.length-pos1);
	    var pos1=fs.search("value=");
	    pos1 += 7;
	    fs=fs.substr(pos1,fs.length-pos1);
	    var pos2=fs.search("\"");
	    fs1 += ','+fs.substr(0,pos2); //max
	    var pos1=fs.search("value=");
	    pos1 += 7;
	    fs=fs.substr(pos1,fs.length-pos1);
	    var pos2=fs.search("\"");
	    fs1 += ','+fs.substr(0,pos2); // step
	    //console.log(fs1);
	    s += '*' + fs1 +'&';
	    cur=cur.nextSibling;
	    continue;
	  }
	}
	var pos=fs.search("<textarea");
	if (pos>=0 && pos<fs.length){
	  // var tmp=field.firstChild.value.replace(/\n/g,'%0a'); tmp=tmp.replace(';','%3b','g');
	  // s += '+' + tmp.replace('&&',' and ','g') + '&';
	  var tmp=encodeURIComponent(field.firstChild.value);
	  s += '+' + tmp + '&';
	  cur=cur.nextSibling;
	  continue;
	}
	pos = fs.search("UI.addhelp");
	if (pos>=0 && pos<fs.length){ cur=cur.nextSibling; continue; }
	s += '+//'+fs+'&';
      }
      cur=cur.nextSibling;
    }
    // Module.print(s);
    s=s.replace(/\"/g,'%22');
    s=s.replace(/>/g,'%3e');
    return s;
  },
  canvas_mousemove:function(event,no){
    if (UI.canvas_pushed){
      // Module.print(event.clientX);
      if (UI.canvas_lastx!=event.clientX){
	if (event.clientX>UI.canvas_lastx)
	  UI.giac_renderer('r'+no);
	else
	  UI.giac_renderer('l'+no);
	UI.canvas_lastx=event.clientX;
      }
      if (UI.canvas_lasty!=event.clientY){
	if (event.clientY>UI.canvas_lasty)
	  UI.giac_renderer('d'+no);
	else
	  UI.giac_renderer('u'+no);
	UI.canvas_lasty=event.clientY;
      }
    }
  },
  show_menu:function(){
    if (document.getElementById('keyboardfunc').style.display=='inline'){
      document.getElementById('keyboardfunc').style.display='none';
    }
    else {
      document.getElementById('keyboardfunc').style.display='inline';
      document.getElementById('keyboard').style.display='none';
      document.getElementById('alpha_keyboard').style.display='none';
      document.getElementById('progbuttons').style.display='none';
      var tab=['boucle','seq','rand','series','int','sum','limit','plotfunc','plotparam',
	       'plotpolar','plotimplicit','plotfield','tabvar','test','prog','solve',
	       'rsolve','diff','matr','suites','arit','geo','linalg','rewrite',
	       'graph','calculus'];
      var s=tab.length,k;
      for (k=0;k<s;++k){
	var tmp=document.getElementById('assistant_'+tab[k]);
	if (tmp.style.display=='block'){
	  tmp.style.display='none';
	  UI.focused=UI.savefocused;
	}
      }
    }
    if (UI.focusaftereval){ UI.focused.focus(); }
  },
  show_config:function(){
    var form=document.getElementById('config');
    form.style.display='inline';
  },
  editline:false,
  set_editline:function(field,b){
    UI.editline=b;
    if (field){
      if (field.parentNode)
	field=field.parentNode;
      else field=field.getTextArea().parentNode;
    }
    if (field){
      //UI.switch_buttons(field,true);
      field=field.firstChild;
      field=field.nextSibling;
      if (field.CodeMirror)
	field=field.nextSibling;
      //console.log(b,field.id);
      if (field && field.id=="")
	field.style.display=b?'inline':'none';
    }
  },
  set_config_width:function(){
    var form=document.getElementById('config');
    var hw=window.innerWidth,hh=window.innerHeight;
    if (hw>=1000){ hw=hw-50; UI.focusaftereval=true;}
    if (hw<=500){ UI.focusaftereval=false; document.getElementById('exportbutton').style.display='none';}
    form.outdiv_width.value=Math.floor(hw/2);
    document.getElementById('mathoutput').style.maxWidth=hw+'px';
    var mh=Math.floor(hh*.61);
    if (UI.editline && UI.detectmob()) mh=Math.floor(hh*.8);
    //console.log('set_config_width hh',document.getElementById('divoutput').style.maxHeight,mh);
    document.getElementById('divoutput').style.maxHeight=mh+'px';
    var w=form.outdiv_width.value,h;
    // Module.print(hw);Module.print(w);
    if (w>hw-300) w=hw-300;
    var hi=hw-w-153;
    if (!UI.qa){ hi=hw-130; w=hi; }
    var hb=29; if (hh>=400) hb=32; if (hh>=500) hb=34; if (hh>600) hb=37;
    //mh=form.outdiv_height.value;
    var cms=mh-2*hb; // codemirror scrollbar max height
    if (UI.focused==cmentree) cms=Math.floor(hw*.67);
    s='h1,h2,h3 { display:inline; font-size:1em;}\ninput[type="number"] { width:40px;}\n .outdiv { width:'+w+'px; max-height: '+mh+'px;  overflow: auto;}\n.filenamecss {width:80px;height:20px}\n.historyinput {width:'+hi+'px;}\n.bouton{vertical-align:bottom; height:'+hb+'px;}\n.CodeMirror-scroll {height:auto; max-height:'+cms+'px;}\n.CodeMirror {border: 1px solid black;  height:auto; min-width:'+hi+'px;}\n  dt {font-family: monospace; color: #666;}';
    //console.log(mh,cms);// Module.print(s);
    //Module.print(mh,cms);
    var st=document.getElementById('document_style');
    st.innerHTML=s;
    var kbd_l=["add_newline","add_infer","add_super","add_left_par","add_right_par",
	       "add_i","add_7" ,"add_8" ,"add_9" ,"add_/",
	       "add_semi" ,"add_abc" ,"add_pi" ,
	       "add_4" ,"add_5" ,"add_6" ,"add_*" ,"add_beg","add_end","add_:",
	       "add_,","add_xtn","add_1" ,"add_2" ,
	       "add_3" ,"add_-" ,"copy_button" ,"curseur_up","add-=" ,
	       "add_dosel","add_ln","add_e","add_0" ,"add_." ,
	       "add_+" ,"curseur_down" ,"shift_key" ,"add_sin" ,"add_cos",
	       "add_tan","add_sqrt","add_^"];
    var kbd_a=["add_alpha_a","add_alpha_b","add_alpha_c","add_alpha_d","add_alpha_e",
	       "add_alpha_f","add_alpha_j","add_alpha_n","add_alpha_r","add_alpha_u","add_alpha_x",
	       "add_alpha_g","add_alpha_k","add_alpha_o","add_alpha_s","add_alpha_v","add_alpha_y",
	       "add_alpha_h","add_alpha_l","add_alpha_p","add_alpha_t","add_alpha_w","add_alpha_z",
	       "add_alpha_i","add_alpha_m","add_alpha_q","add_alpha_{","add_alpha_}",
	       "add_alpha_space","add_alpha_"];
    var kbd_math=["add_arit" ,"add_matr","add_graph","add_calculus",
		  "add_linalg" ,"add_stats","add_tableur","add_rewritetrig","add_solve",
		  "add_mathcomment","add_rand" ,"add_geo","add_rsolve" ,
		  "add_seq","add_tabvar",
		  "add_curseur"];
    var kbd_prog=["add_//","add_nlprog","add_listechaine","add_tortue","add_test",
		  "add_boucle","add_function","add_debug","add_efface","add_avance",
		  "add_recule","add_tourne_gauche","add_tourne_droite",
		  "add_pas_de_cote","add_saute","add_crayon","add_rond","add_disque",
		  "add_rectangle_plein","add_triangle_plein","add_ecris","add_repete","tortue_maillage","tortue_clear"];
    w=Math.floor(hw/12)-1; w=w+"px"; 
    h=Math.floor(hh/20); if (h<34) h=34; h=h+"px"; // console.log(hw,w,hh,h);
    for (var i=0;i<kbd_l.length;i++){
      document.getElementById(kbd_l[i]).style.width=w;
      document.getElementById(kbd_l[i]).style.height=h;
    }
    for (var i=0;i<kbd_a.length;i++){
      document.getElementById(kbd_a[i]).style.width=w;
      document.getElementById(kbd_a[i]).style.height=h;
    }
    w=Math.floor(hw/9)-1; if (w<30) w=30; w=w+"px"; 
    h=Math.floor(hh/20); if (h<35) h=35; h=h+"px"; // console.log(hw,w,hh,h);
    for (var i=0;i<kbd_prog.length;i++){
      document.getElementById(kbd_prog[i]).style.width=w;
      document.getElementById(kbd_prog[i]).style.height=h;
    }
    w=Math.floor(hw/9)-3; if (w<30) w=30; w=w+"px"; 
    h=Math.floor(hh/20); if (h<35) h=35; h=h+"px"; // console.log(hw,w,hh,h);
    for (var i=0;i<kbd_math.length;i++){
      document.getElementById(kbd_math[i]).style.width=w;
      document.getElementById(kbd_math[i]).style.height=h;
    }
    w=Math.floor(hw/9)-3; if (w<30) w=30; w=w+"px"; 
  },
  config_string:function(){
    var form=document.getElementById('config');
    UI.from=form.from.value;
    UI.mailto=form.to.value;
    //console.log(UI.from);
    if (form.qa.checked) UI.qa=true; else UI.qa=false;
    if (form.usecm.checked) UI.usecm=true; else UI.usecm=false; UI.switchcm();
    if (form.fixeddel.checked) UI.fixeddel=true; else UI.fixeddel=false; 
    UI.set_config_width();
    var s;
    var st=document.getElementById('document_style');
    if (form.online_doc.checked)
      UI.docprefix=UI.base_url+'giac/doc/fr/cascmd_fr/';
    else
      UI.docprefix="file://"+form.doc_path.value;
    if (form.prettyprint.checked) UI.prettyprint=true; else UI.prettyprint=false;
    if (form.worker_mode.checked){
      if (!UI.withworker) alert('Session redemarree (variables remises a 0). Les calculs seront faits par un worker.'); UI.withworker=true;
    } else {
      if (UI.withworker) alert('Session redemarree (variables remises a 0).');
      UI.withworker=false;
    }
    if (UI.withworker) document.getElementById('stop_button').style.display='inline'; else document.getElementById('stop_button').style.display='none';
    UI.caseval("autosimplify("+form.autosimp_level.value+")");
    //Module.print(st.innerHTML);
    s='Digits:=';
    s += form.digits_mode.value;
    s += '; angle_radian:=';
    if (form.angle_mode.checked) s += 1; else s += 0;
    s += '; complex_mode:=';
    if (form.complex_mode.checked) s += 1; else s += 0;
    s += '; with_sqrt(';
    if (form.sqrt_mode.checked) s += 1; else s += 0;
    s += '); step_infolevel(';
    if (form.step_mode.checked) s += 1; else s += 0;
    s += ');python_compat(';
    if (form.python_mode.checked) s += 1; else s += 0;
    s += ');';
    // Module.print(s);
    return s;
  },
  set_config:function(setcm_mode){ // b==true if we set cmentree
    var form=document.getElementById('config');
    UI.canvas_w=form.canvas_w.value;
    UI.canvas_h=form.canvas_h.value;
    var s=UI.config_string();
    //console.log(form.wasm_mode);
    UI.addhelp(' ',s);
    document.getElementById('config').style.display='none';
    if (UI.focusaftereval) UI.focused.focus();
    UI.createCookie('xcas_from',form.from.value,10000);
    UI.createCookie('xcas_to',form.to.value,10000);
    UI.createCookie('xcas_digits',form.digits_mode.value,10000);
    UI.createCookie('xcas_angle_radian',form.angle_mode.checked?1:-1,10000);
    UI.createCookie('xcas_python_mode',form.python_mode.checked?1:-1,10000);
    UI.python_mode=form.python_mode.checked;
    if (setcm_mode){
      UI.setoption_mode(cmentree);
    }      
    document.getElementById('add_//').value=UI.python_mode?'#':'//';
    if (!UI.kbdshift) document.getElementById('add_:').value=UI.python_mode?':':':=';
    if (cmentree.type!='textarea') cmentree.options.indentUnit=UI.python_mode?UI.python_indent:2; 
    UI.createCookie('xcas_complex_mode',form.complex_mode.checked?1:-1,10000);
    UI.createCookie('xcas_with_sqrt',form.sqrt_mode.checked?1:-1,10000);
    UI.createCookie('xcas_step_infolevel',form.step_mode.checked?1:-1,10000);
    UI.createCookie('xcas_autosimplify',form.autosimp_level.value,10000);
    UI.createCookie('xcas_docprefix',UI.docprefix,10000);
    UI.createCookie('xcas_withworker',UI.withworker?1:-1,10000);
    UI.createCookie('xcas_wasm',form.wasm_mode.checked?1:-1,10000);
    UI.createCookie('xcas_prettyprint',UI.prettyprint?1:-1,10000);
    UI.createCookie('xcas_qa',UI.qa?1:-1,10000);
    UI.createCookie('xcas_usecm',UI.usecm?1:-1,10000);
    UI.createCookie('xcas_fixeddel',UI.fixeddel?1:-1,10000);
    UI.createCookie('xcas_canvas_w',form.canvas_w.value,10000);
    UI.createCookie('xcas_canvas_h',form.canvas_h.value,10000);
    //UI.createCookie('xcas_outdiv_width',form.outdiv_width.value,10000);
    //UI.createCookie('xcas_outdiv_height',form.outdiv_height.value,10000);
    UI.createCookie('xcas_matrix_maxrows',form.matr_cfg_rows.value,10000);
    UI.createCookie('xcas_matrix_maxcols',form.matr_cfg_cols.value,10000);
    UI.createCookie('xcas_matrix_textarea',form.matr_textarea.checked?1:-1,10000);
    UI.assistant_matr_setmatrix(form.matr_cfg_rows.value,form.matr_cfg_cols.value);
    UI.assistant_matr_setdisplay();
  },
  savesession:function(i){
    // console.log('save_session',i);
    var s;
    filename=document.getElementById("outputfilename").value;
    if (i==2) {
      UI.createCookie('xcas__'+filename,UI.makelink(0),9999);
      console.log(UI.listCookies());
      return;
    }
    if (i==1){
      s=document.getElementById("fulldocument").innerHTML;
      s='<html id="fulldocument" manifest="xcas.appcache">'+s+'</html>';
    }
    else {
      s=document.getElementById("mathoutput").innerHTML;
    }
    var blob = new Blob([s], {type: "text/plain;charset=utf-8"});
    if (i==1) filename += ".html"; else filename += ".xw";
    saveAs(blob,filename);
  },
  show_history123:function(){
    document.getElementById('history1').style.display='inline';
    //document.getElementById('history2').style.display='block';
    document.getElementById('history4').style.display='block';
    document.getElementById('startup').style.display='none';
    document.getElementById('startup1').style.display='none';
    document.getElementById('startup2').style.display='none';
  },
  hide_show:function(tmp){
    if(tmp.style.display=='none')
      tmp.style.display='block';
    else
      tmp.style.display='none'
  },
  loadfile:function(oFiles){
    var nFiles = oFiles.length;
    for (var nFileId = 0; nFileId < nFiles; nFileId++) {
      // Module.print(oFiles[nFileId].name);
      var reader = new FileReader();
      reader.readAsText(oFiles[nFileId]);
      var s;
      reader.onloadend = function(e){		
	s = e.target.result;
	if (s.length>7 && s.substr(0,7)=='<tbody>'){
	  UI.show_history123();
	  document.getElementById("mathoutput").innerHTML += s;
	  if (confirm('Voulez-vous executer les commandes de l\'historique?'))
	    UI.exec(document.getElementById('mathoutput'),0);
	  // Module.print(s);
	}
	else alert('Format de document invalide');
	if (UI.focusaftereval) UI.focused.focus();
      }
    }
  },
  show_level_answers: function(level,b){
    var cur=level.firstChild;
    cur=cur.firstChild;
    cur=UI.skip_buttons(cur); // skip buttons
    var s=cur.innerHTML;
    var pos=s.search("<textarea");
    if (pos<0 || pos>=s.length) return;
    cur=cur.nextSibling; // skip entry field
    if (b)
      cur.style.display='inherit';
    else
      cur.style.display='none';
  },
  show_answers: function(b){
    var out=document.getElementById('mathoutput');
    var cur=out.firstChild;
    while (cur){
      UI.show_level_answers(cur,b);
      cur=cur.nextSibling;
    }
    if (UI.focusaftereval) UI.focused.focus();
  },
  is_alphan:function(c){
    return (c>=48 && c<=57) || (c>=65 && c<=91) || (c>=97 && c<=123) || c==95;
  },
  erase_button:function(newline){
    var s='<td><button class="bouton" onclick=\'UI.erase(this)\' title="';
    s += UI.langue==-1?'placer ce niveau dans la corbeille':'throw this level in the trash';
    s += '">&#x232b;</button>';
    /* if (newline)
       s+='<br>';
       s +='<button class="bouton" onclick=\'UI.reeval(UI.focused,"",false)\'>ok</button>';
    */
    s += '</td></tr>';
    return s;
  },
  move_buttons:function(newline){
    var s='<tr onmouseenter="UI.switch_buttons(this,true)" onmouseleave="if (!UI.fixeddel) UI.switch_buttons(this,false)">';
    // s += '<td>&bull;</td>'; // f=f.nextSibling in switch_buttons
    if (newline){
      s += '<td><button style="width:20px;height:28px;" onclick="UI.moveup(this)" title="';
      s += UI.langue==-1?'d&eacute;placer vers le haut':'move level up';
      s += '">↑</button><br><button style="width:20px;height:28px;" onclick="UI.movedown(this)" title="';
      s += UI.langue==-1?'d&eacute;placer vers la bas':'move level down';
      s += '">↓</button></td><td></td>';
    }
    else {
      s += '<td><button style="width:20px;height:16px;" onclick="UI.moveup(this)" title="';
      s += UI.langue==-1?'d&eacute;placer vers le haut':'move level up';
      s += '">↑</button><button style="width:20px;height:16px;" onclick="UI.movedown(this)" title="';
      s += UI.langue==-1?'d&eacute;placer vers la bas':'move level down';
      s += '">↓</button></td><td><button style="width:20px;height:16px;" onclick="for (var i=0;i<5;i++) UI.moveup(this)" title="';
      s += UI.langue==-1? 'd&eacute;placer de 5 vers le haut':'move level 5 times up';
      s += '">↑↑</button><button style="width:20px;height:16px;" onclick="for (var i=0;i<5;i++) UI.movedown(this)" title="';
      s += UI.langue==-1?'d&eacute;placer de 5 vers la bas':'move level 5 times down';
      s += '">↓↓</button></td>';
    }
    return s;
  },
  skip_buttons:function(field){
    return field.nextSibling.nextSibling;
  },
  addplotfunc:function(){
  },
  paramname:97,
  curseurhtml:function(name,mini,maxi,step,value){
    var s=UI.move_buttons(!UI.qa);
    s += '<td colspan=3>';
    s += '<form onsubmit="setTimeout(function() { rangename.value=valname.value; rangename.step=stepname.value; valname.step=stepname.value;rangename.min=minname.value; rangename.max=maxname.value;UI.eval_below(name.form,name.value,rangename.value);}); return false;">';
    s += '<input class="curseur" type="text" name="name" size="1" value=\''+name+'\'>';
    s += '='+'<input class="curseur" type="number" name="valname" onchange="valname.innerHTML=valname.value" value=\''+value+'\' step=\''+step+'\'>';
    s += '<input class="curseur" type="submit" value="ok">'
    s += '&nbsp;<input class="curseur" type="button" value="--&nbsp;" onclick="rangename.value=valname.value -= 10*stepname.value;UI.eval_below(form,form.name.value,valname.value);">';
    s += '<input class="curseur" type="button" value="&nbsp;-&nbsp;&nbsp;" onclick="rangename.value=valname.value -= stepname.value;UI.eval_below(form,form.name.value,valname.value);">';
    s += '&nbsp;<input class="curseur" type="button" value="&nbsp;&nbsp;+&nbsp;" onclick="rangename.value=valname.value -= -stepname.value;UI.eval_below(form,form.name.value,valname.value);">';
    s += '<input class="curseur" type="button" value="&nbsp;++" onclick="rangename.value=valname.value -= -10*stepname.value;UI.eval_below(form,form.name.value,valname.value);">';
    s += '&nbsp;<input class="curseur" type="button" value="&#x270e;" onclick="var tmp=nextSibling; if (tmp.style.display==\'none\') tmp.style.display=\'inline\'; else tmp.style.display=\'none\';">';
    s += '<span style="display:none">&nbsp;<input class="curseur" type="number" name="minname" value=\''+mini+'\' step=\''+step+'\'>';
    if (window.innerWidth<600)
      s += '<input class="curseur" type="range" style="display:none" name="rangename" onclick="valname.value=value;UI.eval_below(form,form.name.value,value);" value='+value+' min='+mini+' max='+maxi+' step=' + step +'>';
    else 
      s += '<input class="curseur" type="range" name="rangename" onclick="valname.value=value;UI.eval_below(form,form.name.value,value);" value='+value+' min='+mini+' max='+maxi+' step=' + step +'>';
    s += '<input class="curseur" type="number" name="maxname" value=\''+maxi+'\' step=\''+step+'\'>&nbsp;';
    s += '(pas <input class="curseur" type="number" name="stepname" value=\''+step+'\' step=\''+step/100+'\'>)</span>';
    s += '</form>';
    s += '</td>';
    s += UI.erase_button(!UI.qa);
    return s;
  },
  addcurseur: function(name,value,mini,maxi,step){
    UI.show_history123();
    UI.caseval('assume('+name+'='+value+')');
    var s=UI.curseurhtml(name,mini,maxi,step,value);
    var out=document.getElementById('mathoutput');
    //Module.print(s);
    out.innerHTML += s;
    UI.link(0);
    UI.scrollatend(out.parentNode);
    if (UI.focusaftereval) UI.focused.focus();
  },
  exec_history: function(){alert('Historique!');},
  svg_counter:0,
  savesvg: function(field){
    var s=field.innerHTML;
    s='<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n'+s;
    var blob = new Blob([s], {type: "text/plain;charset=utf-8"});
    filename=document.getElementById("outputfilename").value;
    ++UI.svg_counter;
    filename += UI.svg_counter+".svg";
    saveAs(blob,filename);
  },
  zoom: function(field,scale){
    var prev=field.parentNode.previousSibling.lastChild;
    var ps=prev.innerHTML;
    if (ps.length>22 && ps.substr(0,17)==' <canvas id=\"gl3d'){
      ps=ps.substr(18,7);
      var pos=ps.search('"');
      if (pos>0 && pos<7){
	ps=ps.substr(0,pos);
	if (scale>1) UI.giac_renderer('-'+ps); else UI.giac_renderer('+'+ps);
	return;
      }
    }
    if (prev.firstChild) prev=prev.firstChild;
    // firstChild not required with all browsers
    var box = prev.viewBox.baseVal;
    var w=box.width/1.2,h=box.height/1.2;
    var x=box.x+w/10,y=box.y+h/10;
    //Module.print('current w/h '+w+','+h);
    var cx=x+w/2,cy=y+h/2; // center
    w=scale*w; h=scale*h; // new scales
    // Module.print('new center'+cx+','+cy);
    // Module.print('new w/h'+w+','+h);
    x=cx-w/2; y=cy-h/2;
    cx=x+w; cy=y+h;
    // reeval commandline with gl_x=x..cx and gl_y=y..cy
    var postcmd=';gl_x='+x+'..'+cx+';gl_y='+y+'..'+cy+';';
    //Module.print(prev.parentNode.parentNode.previousSibling.innerHTML);
    //Module.print(postcmd);
    if (prev.parentNode.previousSibling){
      //Module.print(prev.parentNode.parentNode.firstChild.innerHTML);
      UI.reeval(prev.parentNode.parentNode.firstChild,postcmd,false);
    }
    else
      UI.reeval(prev.parentNode.parentNode.previousSibling.firstChild,postcmd,false);
  },
  eval_cmdline: function(){
    UI.set_config_width();
    var value;
    document.getElementById('keyboardfunc').style.display='none';
    document.getElementById('keyboard').style.display='none';
    document.getElementById('alpha_keyboard').style.display='none';
    if (cmentree.type!='textarea') value=cmentree.getValue(); else value=entree.value;
    UI.eval_cmdline1(value,true);
  },
  eval_cmdline1:function(value,docaseval){
    UI.set_locale();
    // value=UI.lowercase1(value);
    var out;
    // suppress leading non ascii char
    var n=0;
    for (;n<value.length;n++){
      if (value.charCodeAt(n)>32) break;
    }
    value=value.substr(n,value.length-n);
    for (n=value.length-1;n>=0;n--){
      if (value.charCodeAt(n)>32 || value.charCodeAt(n)==10) break;
    }
    value=value.substr(0,n+1);
    if (value.charCodeAt(n)!=10){
      if (cmentree.type!='textarea')
	cmentree.setValue(value);
      else
	entree.value=value;
    }
    var s=' ';
    if (value.length >= 2 && value.substr(0,2)=='//'){
      out=value;
    } else {
      if (docaseval) {
	if (UI.busy) {out=' Le moteur de calcul est occupe.'; s=out;}
	else {out=UI.casevalcb(value,UI.eval_cmdline1cb,value); return;}
      }
      else { out=' Non evalue. Cliquer sur Exec pour evaluer. '; s=out; }
    }
    UI.eval_cmdline1end(value,out,s);
  },
  eval_cmdline1end:function(value,out,s){
    var add=UI.addinput(value,out,s);
    //var s=UI.caseval('mathml(quote('+value+'),1)');
    //add += '&nbsp;&nbsp;'+s.substr(1,s.length-2);
    //Module.print(value+'  ->  '+out);
    if (UI.focusaftereval) cmentree.focus();
    if (cmentree.type!='textarea') cmentree.execCommand('selectAll');
    else {var f=document.activeElement; cmentree.select(); f.focus(); UI.selection=cmentree.value;}
    //document.getElementById('canvas').focus();
    var mathoutput=document.getElementById('mathoutput');
    var tr=document.createElement("TABLE"); 
    tr.innerHTML += add;
    mathoutput.appendChild(tr.firstChild);
    if (value.length>=2 && value.substr(0,2)=='//'){
      var f=mathoutput.lastChild.firstChild.firstChild.nextSibling.nextSibling.firstChild.nextSibling;
      //console.log(f);
      f.click();
      //UI.selectionne();
    }
    // mathoutput.innerHTML += add;
    UI.render_canvas(mathoutput.lastChild);
    UI.scrollatend(mathoutput.parentNode);
    UI.link(0);
    if (UI.prettyprint && UI.usemathjax && UI.histcount>0)
      //console.log('"hist'+(UI.histcount-1)+'"');
      MathJax.Hub.Queue(["Typeset",MathJax.Hub,'"hist'+(UI.histcount-1)+'"']);
  },
  eval_cmdline1cb: function(out,value){
    var s;
    //console.log(out);
    if (out.length>5 && (out.substr(1,4)=='<svg' || out.substr(0,5)=='gl3d ' || out.substr(0,5)=='gr2d(')) {
      s=out; out='Done_graphic';
    }
    else {
      if (out.length>1 && out[out.length-1]==';')
	out=out.substr(0,out.length-1);
      if (UI.prettyprint){
	if (UI.usemathjax)
	  s='latex(quote('+out+'))';
	else
	  s='mathml(quote('+out+'),1)'; //Module.print(s);
	// console.log(out,s);
	if (out.length>10 && out.substr(0,10)=='GIAC_ERROR')
	  s='"'+out.substr(11,out.length-11)+'"';
	else s=UI.caseval(s);
      } else s=out;
    }
    UI.eval_cmdline1end(value,out,s);
  },
  set_locale: function(){
    if (UI.langue<=0){ 
      var out=UI.caseval('set_language('+-UI.langue+'); ');
      //UI.langue=1; // commente sinon la langue n'est pas toujours reconnue
    }
    if (UI.initconfigstring!=''){
      UI.caseval(UI.initconfigstring);
      UI.initconfigstring=''    
    }
  },
  switch_buttons: function(field,onoff){
    if (!field || !field.firstChild) return;
    var f=field.firstChild;
    // f = f.nextSibling; // &bull; in move_buttons
    if (onoff) f.style.visibility='visible'; else f.style.visibility='hidden';
    f = f.nextSibling;
    if (onoff) f.style.visibility='visible'; else f.style.visibility='hidden';
    f=field.lastChild;
    if (onoff) f.style.visibility='visible'; else f.style.visibility='hidden';
  },
  exec: function(field,start){
    UI.set_locale();
    var cur=field.firstChild;
    var i=0;
    for (;cur;i++){
      if (i>=start)
	UI.eval_level(cur);
      cur=cur.nextSibling;
    }
    if (UI.focusaftereval) UI.focused.focus();
  },
  eval_below: function(field,name,value){
    //console.log(name+':='+value);
    UI.caseval('assume('+name+'='+value+')');
    var cur=field.parentNode.parentNode.parentNode;
    cur=cur.nextSibling;
    //Module.print(cur.innerHTML);
    for (;cur;){
      //console.log(cur);
      UI.eval_level(cur);
      cur=cur.nextSibling;
    }
  },
  rendercomment:function(t){ // replace \n by <br>, for $$ call caseval on mathml or latex(quote())
    var res='',i=0,l=t.length,cas,indollar=false;
    // console.log(t,l);
    for (;i<l;++i){
      var ch=t.charAt(i);
      // console.log(i,ch);
      if (ch=='\n'){ if (!indollar) res+='<br>'; continue; }
      if (ch!='$'){ if (indollar) cas+=ch; else res +=ch; continue; }
      if (!indollar){ indollar=true; cas=''; continue; }
      indollar=false;
      if (UI.usemathjax)
	cas='latex(quote('+cas+'))';
      else
	cas='mathml(quote('+cas+'),1)';
      //console.log(cas);
      cas=UI.caseval(cas);
      //console.log(cas);
      if (cas.charAt(0)=='"' && cas.length>2)
	cas=cas.substr(1,cas.length-2);
      res += cas;
    }
    return res;
  },
  add_math:function(field){
    UI.insert(field,"\$ \$");
    UI.moveCaret(field,-2);
  },
  add_strong:function(field){
    UI.insert(field,"<strong></strong>");
    UI.moveCaret(field,-9);
  },
  add_em:function(field){
    UI.insert(field,"<em></em>");
    UI.moveCaret(field,-5);
  },
  add_red:function(field){
    UI.insert(field,"<font color='red'></font>");
    UI.moveCaret(field,-7);
  },
  add_green:function(field){
    UI.insert(field,"<font color='green'></font>");
    UI.moveCaret(field,-7);
  },
  add_tt:function(field){
    UI.insert(field,"<tt></tt>");
    UI.moveCaret(field,-5);
  },
  add_list:function(field){
    UI.insert(field,"<ul>\n<li>\n<li>\n<li>\n</ul>");
    UI.moveCaretUpDown(field,-3);
  },
  add_enum:function(field){
    UI.insert(field,"<ol>\n<li>\n<li>\n<li>\n</ol>");
    UI.moveCaretUpDown(field,-3);
  },
  add_h1:function(field){
    UI.insert(field,"<h1></h1>");
    UI.moveCaret(field,-5);
  },
  add_h2:function(field){
    UI.insert(field,"<h2></h2>");
    UI.moveCaret(field,-5);
  },
  addcommentafter: function(field){
    var f=field.parentNode.parentNode.parentNode;
    var p=f.parentNode;
    add=UI.addcomment('');
    var tr=document.createElement("TABLE"); 
    tr.innerHTML += add;
    if (f.nextSibling){
      f=f.nextSibling;
      p.insertBefore(tr.firstChild,f);
      f=f.previousSibling;
    }
    else {
      f=p.appendChild(tr.firstChild);
    }
    f.firstChild.firstChild.nextSibling.nextSibling.firstChild.nextSibling.click();
  },
  addcomment: function(text){
    UI.show_history123();
    var s=UI.move_buttons(!UI.qa);
    var t=text.substr(2,text.length-2);
    s += '<td colspan="2"><span style="display:none"><textarea title="';
    s += UI.langue==-1?'Ctrl-Enter ou &#x2705; pour valider ce commentaire':'Ctrl-Enter or &#x2705; will update this comment';
    s += '" onkeypress="UI.ckenter_comment(event,this)" row="5" cols="60">'+t+'</textarea>';
    s += '<button class="bouton" title="';
    s += UI.langue==-1?'Valide ce commentaire':'Update comment';
    s += '" onclick="UI.editcomment_end(this)">&#x2705;</button>';
    s += '<br><button onmousedown="event.preventDefault()" title="';
    s += UI.langue==-1?'Ajoute $ $ pour ins&eacute;rer des maths':'Add $ $ to insert maths';
    s += '" class="bouton" onclick="UI.add_math(UI.focused)">math</button>';
    s += '<button onmousedown="event.preventDefault()" title="'
    s += UI.langue==-1?'Passe en police fixe':'Fixed size police';
    s += '" class="bouton" onclick="UI.add_tt(UI.focused)"><tt>Abc</tt></button>';
    s += '<button title="';
    s += UI.langue==-1?'Passe en gras':'Boldface';
    s += '" onmousedown="event.preventDefault()"  class="bouton" onclick="UI.add_strong(UI.focused)"><strong>Abc</strong></button>';
    s += '<button title="';
    s += UI.langue==-1?'Passe en italique':'italics';
    s += '" onmousedown="event.preventDefault()" class="bouton" onclick="UI.add_em(UI.focused)"><em>Abc</em></button>';
    s += '<button title="Red/Rouge" onmousedown="event.preventDefault()" class="bouton" onclick="UI.add_red(UI.focused)"><font color="red">Abc</font></button>';
    s += '<button title="Green/Vert" onmousedown="event.preventDefault()" class="bouton" onclick="UI.add_green(UI.focused)"><font color="green">Abc</font></button>';
    s += '<button onmousedown="event.preventDefault()" title="';
    s += UI.langue==-1?'Ins&egrave;re une liste':'List insertion';
    s += '" class="bouton" onclick="UI.add_list(UI.focused)">list</button>';
    s += '<button onmousedown="event.preventDefault()" title="';
    s += UI.langue==-1?'Ins&egrave;re une listenum&eacute;rot&eacute;e':'Numbered list insertion';
    s += '" class="bouton" onclick="UI.add_enum(UI.focused)">num</button>';
    s += '<button style="display:none" onmousedown="event.preventDefault()" class="bouton" onclick="UI.add_h2(UI.focused)">sous</button>';
    s += UI.langue==-1? '<button onmousedown="event.preventDefault()" title="Ins&egrave;re un titre" class="bouton" onclick="UI.add_h1(UI.focused)">titre</button>':'<button onmousedown="event.preventDefault()" title="Insert title" class="bouton" onclick="UI.add_h1(UI.focused)">title</button>';
    s += '</span><span onclick="UI.editcomment1(this)">'+UI.rendercomment(t)+'</span></td>';
    s += '<td> <button title="';
    s += UI.langue==-1?'Editer ce commentaire':'Edit this comment';
    s += '" style="width:20px;height:30px;" onclick="UI.editcomment2(this);">&#x270e;</td>';
    s += UI.erase_button(!UI.qa);
    return s;
  },
  editcomment1: function(field){
    field.style.display='none';
    var prev=field.parentNode;
    prev.firstChild.style.display='inline';
    // console.log(prev.firstChild.firstChild.innerHTML);
    UI.focused=prev.firstChild.firstChild;
    UI.resizetextarea(UI.focused);
    UI.focused.focus();
    prev.nextSibling.style.display='none';
  },
  editcomment2 : function(field){
    var prev=field.parentNode.previousSibling;
    prev.firstChild.style.display='inline';
    UI.focused=prev.firstChild.firstChild;
    UI.resizetextarea(UI.focused);
    UI.focused.focus();
    prev.lastChild.style.display='none';
    field.parentNode.style.display='none';
  },
  editcomment_end: function(field){
    var prev=field.previousSibling;
    var s=prev.value;
    var par=field.parentNode;
    par.style.display='none';
    par.nextSibling.style.display='inline';
    par.nextSibling.innerHTML=UI.rendercomment(s);
    par.parentNode.nextSibling.style.display='inline';
    UI.focused=cmentree;
    UI.link(0);
  },
  eval: function(text,textin){
    UI.set_locale();
    var out=UI.caseval(text);
    //console.log(text,out);
    var s=' ';
    if (out.substr(1,4)=='<svg' || out.substr(0,5)=='gl3d ' || out.substr(0,5)=='gr2d('){
      // Module.print(text+' -> Done');
      s=out; out='Done_graphic';
    }
    else {
      // Module.print(text+' -> '+out);
      if (UI.prettyprint){
	if (UI.usemathjax)
	  s=UI.caseval('latex(quote('+out+'))');
	else
	  s=UI.caseval('mathml(quote('+out+'),1)');
      } else s=out;
    }
    s=UI.addinput(textin,out,s);
    return s;
  },
  render_canvas:function(field){
    // return; // does not work, 
    var n=field.id;
    if (n && n.length>5 && n.substr(0,5)=='gr2d_'){
      //console.log(field.parentNode.innerHTML);
      UI.turtle_draw(n,field.nextSibling.value);
    }
    if (n && n.length>5 && n.substr(0,5)=='gl3d_'){
      Module.print(n);
      var n3d=n.substr(5,n.length-5);
      //Module.print(n3d);
      //Module.canvas=document.getElementById(n);
      UI.giac_renderer(n3d);
      //Module.canvas=document.getElementById('canvas');
      return;
    }
    var f=field.firstChild;
    for (;f;f=f.nextSibling){
      UI.render_canvas(f);
    }
  },
  search:function(field,cmd){
    if (!field) return;
    field=field.parentNode;
    if (field){
      if (field){
	if (field.parentNode)
	  field=field.parentNode;
	if (field){
	  field=field.firstChild;
	  if (field){
	    var cm=field.nextSibling.CodeMirror;
	    if (field.id=='entree') cm=cmentree;
	    if (cm){
	      if (cmd==0){ CodeMirror.commands.find(cm); return;}
	      if (cmd==1){ CodeMirror.commands.findNext(cm); return;}
	      if (cmd==2){ CodeMirror.commands.findPrev(cm); return;}
	      if (cmd==3){ CodeMirror.commands.replace(cm); return;}
	      if (cmd==4){ CodeMirror.commands.replaceAll(cm); return;}
	      if (cmd==5){ CodeMirror.commands.jumpToLine(cm); return;}
	      if (cmd==6){ cm.undo(); return;}
	      if (cmd==7){ cm.redo(); return;}
	      if (cmd==-1){ UI.completion(cm); return;}
	    }
	  }
	}
      }
    }
  },
  evallevel:function(field,eval){
    if (!field) return;
    field=field.parentNode;
    if (field){
      field.style.display='none'; // hide ok button
      if (field){
	if (field.parentNode)
	  field=field.parentNode;
	if (field){
	  field=field.firstChild;
	  if (field){
	    if (field.nextSibling.CodeMirror){ // convert codemirror back
	      var cm=field.nextSibling;
	      cm.CodeMirror.toTextArea();
	    }
	    if (eval) UI.reeval(field,'',false); else UI.link(0);
	  }
	}
      }
    }
  },
  reeval: function(field,postcmd,focusnextsibling){
    var field_=field;
    // field=field.previousSibling;
    UI.set_config_width();
    if (field.type!='textarea'){ var t=field.getTextArea(); t.value=field.getValue();field=t;}
    UI.set_editline(field,false);
    var s=field.value;
    //console.log(s);
    var par=field.parentNode;
    par=par.parentNode;
    if (s.length && s[s.length-1]==';' && postcmd.length && postcmd[0]==';') postcmd=postcmd.substr(1,postcmd.length-1);
    s=UI.eval(s+postcmd,s);
    par.innerHTML=s;
    UI.render_canvas(par);
    UI.link(0);
    if (UI.prettyprint && UI.usemathjax && UI.histcount>0){
      //console.log('"hist'+(UI.histcount-1)+'"');
      MathJax.Hub.Queue(["Typeset",MathJax.Hub,'"hist'+(UI.histcount-1)+'"']);
    }
    if (UI.focusaftereval){
      if (focusnextsibling){
	par=par.parentNode.nextSibling;
	if (par==null) cmentree.focus(); 
	else {
	  par=par.firstChild.firstChild.nextSibling.nextSibling;
	  par=par.firstChild;
	  if (par.style.display=='none'){ // commentaire
	    par=par.nextSibling;
	    if (par.CodeMirror){
	      par=par.CodeMirror;
	      UI.focused=par;
	      par.focus();
	    }
	    else
	      par.click();
	  }
	  else {
	    par.focus();
	  }
	}
      }
      else
	cmentree.focus();       
    }
  },
  eval_level: function(field){
    // ? use cur.nodeType instead of search?
    var s=field.innerHTML;
    var pos=s.search("<textarea");
    if (pos<0 || pos>=s.length){
      pos=s.search("<form");
      if (pos>0 && pos<s.length){
	var level=field.firstChild;
	var cur=level.firstChild;
	cur=UI.skip_buttons(cur);
	//console.log(cur);
	cur=cur.firstChild;
	//Module.print(cur.name.value+':='+cur.rangename.value);
	UI.caseval(cur.name.value+':='+cur.rangename.value);
	var s=UI.curseurhtml(cur.name.value,cur.minname.value,cur.maxname.value,cur.stepname.value,cur.valname.value);
	level.innerHTML=s;
      }
      return;
    }
    var cur=field.firstChild;
    cur=cur.firstChild;
    cur=UI.skip_buttons(cur);
    cur=cur.firstChild;
    var tst=cur.firstChild;
    if (tst!=undefined && tst.nextSibling!=undefined){ // commentaire
      tst.nextSibling.click();
      return;
    }
    s=cur.value;
    s=UI.eval(s,s);
    field.innerHTML=s;
    UI.render_canvas(field);
    if (UI.prettyprint && UI.usemathjax ){
      //console.log(s);
      MathJax.Hub.Queue(["Typeset",MathJax.Hub,field]);
    }
  },
  before: function(field){
    var s='';
    while ((field=field.previousSibling)){
      s += field.innerHTML;
    }
    return s;
  },
  after: function(field){
    var s='';
    while ((field=field.nextSibling)){
      s += field.innerHTML;
    }
    return s;
  },
  prepare_cm: function(txt,h,cm){
    var pos=txt.selectionStart;
    var i,s=txt.value,l=0,c=0;
    for (i=0;i<pos;++i){
      if (s[i]=='\n'){
	l++; c=0;
      }
      else c++;
    }
    cm.setCursor({line:l,ch:c}); cm.refresh();
    UI.setoption_mode(cm);
    //cm.setSize(null,h+20); // commented (auto-resize)
    cm.on("focus",function(cm){
      UI.set_focused(cm);
      UI.set_editline(cm,true); // insure OK is visible on mobile
      UI.set_config_width();
    });
    cm.on("blur",function(cmf) {
      //cmf.getTextArea().value=cmf.getValue();
      //UI.resizetextarea(cmf.getTextArea());
      if (cmf.getSelection().length > 0){UI.selection=cmf.getSelection();}
      //UI.set_editline(cm,false);
      //UI.set_config_width();
      //cmf.toTextArea();
    });
    // cm.setOption("inputStyle", "textarea");
    cm.setOption("extraKeys", {
      Enter: function(cm){
	// Enter inserts \n except on empty line (two Enter without indent reevals)
	var start=cm.getCursor('from');
	var end=cm.getCursor('to');
	if ( end.line!=start.line || end.ch!=start.ch || ( (start.line>0 || start.ch>0) && cm.getLine(end.line).length>0)){
	  UI.insert(cm,'\n');
	  return;
	}
	var txt=cm.getTextArea();
	cm.toTextArea();
	UI.reeval(txt,'',true);
      },
      "Ctrl-Enter": function(cm){
	var txt=cm.getTextArea();
	cm.toTextArea();
	UI.reeval(txt,'',true);
      },
      Backspace: function(cm){
	UI.backspace(cm);
      },
      F1: function(cm) {
	UI.completion(cm);
      },
      Tab: function(cm) {
	UI.indentline(cm);
	//cm.toTextArea();  
      }
    });
  },
  count_newline: function(text){
    var k=0,r=0;
    for (;k<text.length;++k){
      if (text.charCodeAt(k)==10)
	++r;
    }
    return r;
  },
  addinput: function(textin,textout,mathmlout){
    document.getElementById('startup_restore').style.display='none'
    //console.log(textin,textout,mathmlout); 
    if (mathmlout.length>=5 && mathmlout.substr(0,5)=='gl3d '){ document.getElementById('table_3d').style.display='inherit';}
    if (textin.length >= 2 && textin.substr(0,2)=='//') return UI.addcomment(textin);
    UI.show_history123();
    // document.getElementById('mathoutput').style.listStyleType = 'none';
    var is_svg=mathmlout.substr(1,4)=='<svg';
    var is_3d=mathmlout.substr(0,5)=='gl3d ';
    var is_gr2d=mathmlout.substr(0,5)=='gr2d(';
    var s=UI.move_buttons(!UI.qa);
    var delbut=false;
    if (textin.charCodeAt(0)==63)
      s += '<td colspan="2">'+UI.renderhelp(textout)+'</td><td>';
    else {
      if (UI.qa)
	s += '<td>';
      else
	s += '<td colspan=2>';	
      s += '<textarea class="historyinput" ';
      if (is_svg && UI.qa)
	s+='rows=8 style="font-size:large"';
      else
	//s += 'rows='+(UI.count_newline(textin)+1) +' style="font-size:large"';
	s += 'style="height:'+(20+16*UI.count_newline(textin))+'px; font-size:large"';
      s += ' title="Enter: saut de ligne, Ctrl-Enter: eval" onkeypress="UI.ckenter(event,this)" onblur="UI.updatelevel(this);" onfocus="if (UI.usecm) {var h=offsetHeight;UI.history_cm=CodeMirror.fromTextArea(this,{ matchBrackets: true,lineNumbers:true,viewportMargin: Infinity}); UI.history_cm.setCursor({line:0,ch:selectionStart});UI.history_cm.options.indentUnit=UI.python_mode?UI.python_indent:2; UI.prepare_cm(this,h,UI.history_cm);UI.changefontsize(UI.history_cm,16); UI.set_focused(UI.history_cm);} else UI.set_focused(this); UI.set_editline(this,true); UI.set_config_width(); parentNode.scrollIntoView();" onselect="if (UI.getsel(this).length>0) UI.selection=UI.getsel(this);">'+textin+'</textarea>';
      s += '<span style="display:none">';
      s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.evallevel(this,true)" title="';
      s += UI.langue==-1?'R&eacute;evaluer le niveau (Ctrl-Enter)':'Reeval level (Ctrl-Enter)';
      s += '">&nbsp;&#x2705;&nbsp;&nbsp;</button>';
      s += '<button class="bouton" onmousedown="event.preventDefault()" onClick="UI.search(this,-1);" title="';
      s += UI.langue==-1?'Donne une aide courte et quelques exemples d\'utilisation d\'une commande.':'Short help and examples on a command';
      s += '">&nbsp;?&nbsp;</button>';
      s += '<button class="bouton" onmousedown="event.preventDefault()" onClick="UI.move_caret_or_focus(UI.focused,-1)" title="cursor ←">&nbsp;←&nbsp;</button>'
      s += '<button class="bouton" onmousedown="event.preventDefault()" onClick="UI.move_caret_or_focus(UI.focused,1)" title="cursor →">&nbsp;→&nbsp;</button>'
      s += '<button class="bouton" onmousedown="event.preventDefault()" onClick="UI.moveCaretUpDown(UI.focused,-1)" title="cursor ↑">↑&nbsp;</button>'
      s += '<button class="bouton" onmousedown="event.preventDefault()" onClick="UI.moveCaretUpDown(UI.focused,1)" title="cursor ↓">&nbsp;↓</button>'
      s += '<button class="bouton" onmousedown="event.preventDefault()" onClick="UI.indentline(UI.focused)" title="Indent">→|</button>'
      s += '<button class="bouton" onmousedown="event.preventDefault()" onClick="UI.backspace(UI.focused)" title="';
      s += UI.langue==-1?'Efface':'Erase';
      s += '">&#x232b;</button>'
      if (UI.usecm){
	//s += '<br>';
	s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.search(this,6)" title="';
	s += UI.langue==-1?'Annuler':'Undo';
	s +='"><img width="16" height="16" src="undo.png" alt="Annuler" align="center"></button>';
	s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.search(this,7)" title="';
	s += UI.langue==-1?'Refaire':'Redo';
	s+='"><img width="16" height="16" src="redo.png" alt="Redo" align="center"></button>';
	s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.search(this,0)" title="';
	s += UI.langue==-1?'Rechercher':'Find';
	s += '">find</button><button class="bouton" onmousedown="event.preventDefault()" onclick="UI.search(this,1)" title="';
	s += UI.langue==-1?'Rechercher suivant':'Find next';
	s += '">&#x21D2;</button><button class="bouton" onmousedown="event.preventDefault()" onclick="UI.search(this,2)" title="';
	s += UI.langue==-1?'Rechercher pr&eacute;c&eacute;dent':'Find previous';
	s += '">&#x21D0;</button>';
	s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.search(this,3)" title="';
	s += UI.langue==-1?'Remplacer':'Replace';
	s += '">rep</button><button class="bouton" onmousedown="event.preventDefault()" onclick="UI.search(this,5)" title="';
	s += UI.langue==-1?'Aller ligne':'Go line';
	s += '">go</button>';
      }
      s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.evallevel(this,false)" title="';
      s += UI.langue==-1?'Abandonner':'Cancel';
      s += '">&nbsp;&#x274C;</button>';
      s += '</span>';
      if (UI.qa) s += '</td>'; 
      if (is_svg || is_3d || is_gr2d){
	if (UI.qa) s += '<td>'; else s+='<br>';
	if (is_svg)
	  s += '<div style="text-align:center">'+mathmlout.substr(1,mathmlout.length-2)+'</div></td>';
	else {
	  if (is_gr2d){
	    var gr2ds='gr2d_'+UI.gr2d_ncanvas;
	    s+="<div style='text-align:center'> <canvas id='"+gr2ds+"' width="+UI.canvas_w+" height="+UI.canvas_h+"> </canvas><textarea style='display:none'>"+mathmlout+"</textarea></div></td>";
	    UI.gr2d_ncanvas++;
	  }
	  else {
	    var n3d=mathmlout.substr(5,mathmlout.length-5);
	    //Module.print(n3d);
	    if (0)
	      s += '<div style="text-align:center"> 3d </div></td>';
	    else s += '<div style="text-align:center"> <canvas id="gl3d_'+n3d+'" onmousedown="UI.canvas_pushed=true;UI.canvas_lastx=event.clientX; UI.canvas_lasty=event.clientY;" onmouseup="UI.canvas_pushed=false;" onmousemove="UI.canvas_mousemove(event,'+n3d+')" width='+400+' height='+250+'></canvas></div></td>';
	    //Module.print(s);
	  }
	}
	s+='<td>';
	if (!is_gr2d) {
	  s += '<button  style="width:32px;height:30px;" onclick="UI.zoom(this,1.414)">out</button><br>';
	  s += '<button  style="width:32px;height:30px;" onclick="UI.zoom(this.previousSibling,0.707)">in</button><br>';
	}
	if (is_svg) s += '<button style="width:32px;height:30px;" onclick="UI.savesvg(parentNode.previousSibling)">sav</button><br>';
	s += '<br><button style="width:32px;height:30px;" onclick=\'UI.erase(this)\' title="';
	s += UI.langue==-1?'placer ce niveau dans la corbeille':'throw this level in the trash';
	s += '">&#x232b;</button>'; delbut=true;
	s += '</td>';
      }
      else {
	if (UI.qa) s += '<td>';
	s += '<div style="color:blue; text-align:center" title="';
	s += UI.langue==-1?'Double clic: voir en mode texte (utile pour copier-coller)':'Double clic: view answer in text mode, useful for copy/paste';
	s += '" class="outdiv" ondblclick="nextSibling.style.display=\'inherit\';this.nextSibling.select();UI.selection=nextSibling.value;this.style.display=\'none\';this.nextSibling.nextSibling.style.display=\'inherit\';" id="hist'+UI.histcount+'">';
	UI.histcount++;
	if (UI.prettyprint){
	  if (UI.usemathjax)
	    s += '$$'+mathmlout.substr(1,mathmlout.length-2)+'$$';
	  else
	    s += mathmlout.substr(1,mathmlout.length-2);
	} else s += mathmlout;
	s += '</div>';
	s += '<textarea class="outdiv" onfocus="UI.set_focused(this)" onselect="if (UI.getsel(this).length>0) UI.selection=UI.getsel(this);" style="display:none">'+textout+'</textarea>';
	s += '<button style="display:none" onclick="previousSibling.previousSibling.style.display=\'block\'; previousSibling.style.display=\'none\';this.style.display=\'none\'">cancel</button>';
	s += '</td><td>';
	s += '<button style="width:20px;height:30px;" onclick="UI.addcommentafter(this)" title="';
	s += UI.langue==-1?'Ajouter un commentaire':'Add a comment';
	s += '" >&#x270e;</button>';
	//s += '<button style="width:20px;height:30px;" onclick=\'UI.insert(UI.focused,decodeURIComponent("evalf('+encodeURIComponent(textin)+')"))\' title="Valeur approch&eacute;e" style="color:blue">~</button>';
	//s += '<button style="width:20px;height:30px;" onclick=\'UI.insert(UI.focused,decodeURIComponent("latex('+encodeURIComponent(textin)+')"))\' title="convertir en LaTeX" style="color:blue">TeX</button>';
	if (!UI.qa) {
	  s += '<button style="height:25px;" onclick=\'UI.erase(this)\' title="';
	  s += UI.langue==-1?'placer ce niveau dans la corbeille':'throw this level in the trash';
	  s += '">del</button>';
	  delbut=true;
	}
	s +='</td>';
      }
    }
    if (delbut) s += '</tr>'; else s += UI.erase_button(!UI.qa);
    // console.log(s);
    return s;
  },
  giac_renderer: function(text){
    var gr = Module.cwrap('_ZN4giac13giac_rendererEPKc','number', ['string']);
    gr(text);
  },
  xcascmd:["ABS","ACOS","ACOSH","ACOT","ACSC","ADDCOL","ADDROW","ALOG","ARC","ARG","ASEC","ASIN","ASINH","ATAN","ATANH","Airy_Ai","Airy_Bi","Ans","Archive","BINOMIAL","BesselI","BesselJ","BesselK","BesselY","Beta","Bezier","BlockDiagonal","CEILING","CHOOSE","COLNORM","COMB","CONCAT","COND","CONJ","COS","COSH","COT","CROSS","CSC","Celsius2Fahrenheit","Ci","Ci0","Circle","ClrDraw","ClrGraph","ClrIO","CopyVar","CyclePic","DEGXRAD","DELCOL","DELROW","DET","DISP","DOT","DROP","DUP","DelFold","DelVar","Det","Dirac","DispG","DispHome","DrawFunc","DrawInv","DrawParm","DrawPol","DrawSlp","DrwCtour","EDITMAT","EIGENVAL","EIGENVV","EXP","EXPM1","EXPORT","Ei","Ei0","Ei_f","Eta","Exec","FLOOR","FNROOT","Factor","Fahrenheit2Celsius","Fill","GETKEY","GF","Gamma","Gcd","Gcdex","Get","GetCalc","GetFold","Graph","HMSX","Heaviside","IDENMAT","IFTE","IM","INPUT","INVERSE","ISOLATE","ITERATE","Input","InputStr","Int","Inverse","JordanBlock","LINE","LN","LNP1","LOG","LQ","LSQ","LU","Line","LineHorz","LineTan","LineVert","MAKELIST","MAKEMAT","MANT","MAX","MAXREAL","MIN","MINREAL","MOD","MSGBOX","NOP","NORMALD","NTHROOT","NewFold","NewPic","Nullspace","OVER","Output","Ox_2d_unit_vector","Ox_3d_unit_vector","Oy_2d_unit_vector","Oy_3d_unit_vector","Oz_3d_unit_vector","PERM","PICK","PIECEWISE","PIXOFF","PIXON","POISSON","POLYCOEF","POLYEVAL","POLYFORM","POLYROOT","POS","PRINT","Pause","Phi","Pictsize","PopUp","Prompt","Psi","Psi_minus_ln","PtOff","PtOn","PtText","PxlOff","PxlOn","QR","QUAD","QUOTE","Quo","RADXDEG","RANDMAT","RANDOM","RANDSEED","RANK","RCL","RE","RECT","RECURSE","REDIM","REPLACE","REVERSE","ROUND","ROWNORM","RREF","RandSeed","Rank","RclPic","Rem","Resultant","RplcPic","Rref","SCALE","SCALEADD","SCHUR","SEC","SIGN","SIN","SINH","SIZE","SORT","SPECNORM","SPECRAD","SUB","SVD","SVL","SWAP","SWAPCOL","SWAPROW","SetFold","Si","SiCi_f","SiCi_g","SortA","SortD","StoPic","Store","Sum","TAN","TANH","TAYLOR","TRACE","TRN","TRUNCATE","TeX","UTPC","UTPF","UTPN","UTPT","Unarchiv","VIEWS","WAIT","XHMS","XPON","Zeta","ZoomRcl","ZoomSto","a2q","abcuv","about","abs","abscissa","accumulate_head_tail","acos","acos2asin","acos2atan","acosh","acot","acsc","add","add_language","additionally","adjoint_matrix","affix","algvar","alog10","alors","altitude","and","angle","angleat","angleatraw","animate","animate3d","animation","ans","append","apply","approx","arc","arcLen","area","areaat","areaatraw","areaplot","arg","array","array_sto","as_function_of","asc","asec","asin","asin2acos","asin2atan","asinh","assign","assume","atan","atan2acos","atan2asin","atanh","atrig2ln","augment","avance","avgRC","background","baisse_crayon","bar_plot","barycenter","basis","bernoulli","bezout_entiers","binomial","binomial_cdf","binomial_icdf","binprint","bisector","bitand","bitmap","bitor","bitxor","black","blockmatrix","blue","border","bounded_function","boxwhisker","break","breakpoint","by","c1oc2","c1op2","cFactor","cSolve","cZeros","cache_tortue","calc_mode","camembert","canonical_form","cap","cas_setup","cat","cd","ceil","ceiling","cell","center","center2interval","centered_cube","centered_tetrahedron","cfactor","changebase","char","charpoly","chinrem","chisquare","chisquare_cdf","chisquare_icdf","cholesky","choosebox","chrem","circle","circumcircle","classes","click","close","coeff","coeffs","col","colDim","colNorm","coldim","collect","colnorm","color","colspace","comDenom","comb","combine","comment","common_perpendicular","companion","compare","complexroot","concat","cone","conic","conj","cont","contains","content","contourplot","convert","convertir","convexhull","coordinates","copy","correlation","cos","cos2sintan","cosh","cot","cote","count","count_eq","count_inf","count_sup","courbe_parametrique","courbe_polaire","covariance","covariance_correlation","cpartfrac","crationalroot","crayon","cross","crossP","cross_ratio","crossproduct","csc","csolve","csv2gen","cube","curvature","cumSum","cumulated_frequencies","curl","current_sheet","curve","cyan","cycle2perm","cycleinv","cycles2permu","cyclotomic","cylinder","de","deSolve","debug","debug_infolevel","debut_enregistrement","decrement","degree","delcols","delrows","deltalist","denom","densityplot","deriver","desolve","dessine_tortue","det","det_minor","developper","developper_transcendant","dfc","dfc2f","diag","diff","dim","display","disque","disque_centre","distance","distance2","distanceat","distanceatraw","div","divcrement","divergence","divide","divis","division_point","divisors","divpc","dodecahedron","dot","dotP","dotprod","droit","droite_tangente","dsolve","e2r","ecart_type","ecart_type_population","ecris","efface","egcd","egv","egvl","eigVc","eigVl","eigenvals","eigenvalues","eigenvectors","eigenvects","element","ellipse","else","entry","envelope","epsilon2zero","equal2diff","equal2list","equation","equilateral_triangle","erase3d","erf","erfc","erfs","et","euler","euler_mac_laurin","eval","eval_level","evala","evalb","evalc","evalf","evalm","even","evolute","exact","exbisector","excircle","execute","exp","exp2list","exp2pow","exp2trig","expexpand","exponential_regression","exponential_regression_plot","expr","extract_measure","ezgcd","f2nd","fMax","fMin","fPart","faces","facteurs_premiers","factor","factor_xn","factorial","factoriser","factoriser_entier","factoriser_sur_C","factoriser_xn","factors","faire","fclose","fcoeff","ffonction","fft","fieldplot","filled","fin_enregistrement","findhelp","fisher","fisher_cdf","fisher_icdf","float","float2rational","floor","fonction","fonction_derivee","fopen","for","format","fourier_an","fourier_bn","fourier_cn","fprint","frac","fracmod","frame_2d","frame_3d","froot","fsolve","funcplot","function_diff","fxnd","gauche","gauss","gaussjord","gbasis","gcd","gcdex","genpoly","geo2d","geo3d","getDenom","getKey","getNum","getType","giac","goto","grad","gramschmidt","graph2tex","graph3d2tex","graphe","graphe3d","graphe_suite","greduce","green","groupermu","hadamard","half_cone","half_line","halftan","halftan_hyp2exp","halt","hamdist","harmonic_conjugate","harmonic_division","has","hasard","head","heap_mult","hermite","hessenberg","hessian","heugcd","hexagon","hexprint","hidden_name","hilbert","histogram","hold","homothety","horner","hp38","hyp2exp","hyperbola","hyperplan","hypersphere","hypersurface","iPart","iabcuv","ibasis","ibpdv","ibpu","ichinrem","ichrem","icontent","icosahedron","id","identity","idivis","idn","iegcd","if","ifactor","ifactors","ifft","igcd","igcdex","ihermite","ilaplace","im","imag","image","implicitplot","implicitplot3d","inString","in_ideal","incircle","increment","indets","inequationplot","input","inputform","insmod","int","intDiv","integer_format","integrate","integrer","inter","interactive","interactive_odeplot","interactive_plotode","interp","interval2center","inv","inverse","inversion","invlaplace","invztrans","iquo","iquorem","iratrecon","irem","isPrime","is_collinear","is_concyclic","is_conjugate","is_coplanar","is_cycle","is_element","is_equilateral","is_harmonic","is_harmonic_circle_bundle","is_harmonic_line_bundle","is_orthogonal","is_parallel","is_parallelogram","is_permu","is_perpendicular","is_prime","is_pseudoprime","is_rectangle","is_rhombus","is_square","ismith","isobarycenter","isom","isopolygon","isprime","ithprime","jacobi_symbol","jordan","jusque","ker","kernel","keyboard","kill","l1norm","l2norm","label","lagrange","laguerre","laplace","laplacian","latex","lcm","lcoeff","ldegree","left","legend","legendre","legendre_symbol","length","leve_crayon","lgcd","lhs","ligne_polygonale","ligne_polygonale_pointee","limit","limite","lin","line","line_inter","line_segments","linear_interpolate","linear_regression","linear_regression_plot","lineariser","lineariser_trigo","linsolve","lis","lis_phrase","list2mat","listplot","lll","ln","lnGamma_minus","lname","lncollect","lnexpand","locus","log10","logarithmic_regression","logarithmic_regression_plot","logb","logistic_regression","logistic_regression_plot","lsmod","lu","lvar","mRow","mRowAdd","magenta","makelist","makemat","makemod","makesuite","makevector","map","maple2mupad","maple2xcas","maple_ifactors","maple_mode","mat2list","mathml","matpow","matrix","max","maxnorm","mean","median","median_line","member","mid","midpoint","min","mkisom","mksa","modgcd","modgcd_cachesize","modp","mods","montre_tortue","moustache","moyal","moyenne","mpzclass_allowed","mul","mult_c_conjugate","mult_conjugate","multcrement","multiplier_conjugue","multiplier_conjugue_complexe","multiply","mupad2maple","mupad2xcas","nCr","nDeriv","nInt","nPr","nSolve","ncols","newList","newMat","newton","nextperm","nextprime","nodisp","non","non_recursive_normal","nop","nops","norm","normal","normal_cdf","normal_icdf","normald","normald_cdf","normald_icdf","normalize","nrows","nuage_points","nullspace","numer","octahedron","octprint","odd","odeplot","odesolve","op","open","open_polygon","or","ord","order_size","ordinate","orthocenter","orthogonal","os_version","ou","output","p1oc2","p1op2","pa2b2","pade","padic_linsolve","parabola","parabolic_interpolate","parallel","parallelepiped","parallelogram","parameq","parameter","paramplot","pari","pari_unlock","part","partfrac","pas","pas_de_cote","pcar","pcar_hessenberg","pcoeff","perimeter","perimeterat","perimeteratraw","perm","perminv","permu2cycles","permu2mat","permuorder","perpen_bisector","perpendicular","peval","piecewise","pivot","pixoff","pixon","plane","plot","plot3d","plot_style","plotarea","plotcontour","plotdensity","plotfield","plotfunc","plotimplicit","plotinequation","plotlist","plotode","plotparam","plotpolar","plotseq","pmin","pnt","point","point2d","point3d","pointer","poisson","poisson_cdf","poisson_icdf","polar","polar2rectangular","polar_coordinates","polar_point","polarplot","pole","poly2symb","polyEval","polygone_rempli","polygonplot","polygonscatterplot","polyhedron","polynomial_regression","polynomial_regression_plot","position","potential","pour","pow2exp","power_regression","power_regression_plot","powermod","powerpc","powexpand","powmod","prepend","preval","prevperm","prevprime","primpart","print","printpow","prism","product","prog_eval_level","projection","proot","propFrac","propfrac","psrgcd","ptayl","purge","pwd","pyramid","q2a","qr","quadric","quadrilateral","quantile","quartile1","quartile3","quartiles","quaternion","quest","quo","quorem","quote","r2e","radical_axis","radius","ramene","rand","randMat","randNorm","randPoly","randexp","randmatrix","randperm","randpoly","randvector","range","rank","ranm","rassembler_trigo","rat_jordan","rat_jordan_block","rationalroot","ratnormal","rdiv","re","read","readrgb","readwav","real","realroot","reciprocation","rectangle","rectangle_plein","rectangular2polar","rectangular_coordinates","recule","red","reduced_conic","reduced_quadric","ref","reflection","rem","remain","remove","remove_language","reorder","repete","reset_solve_counter","residue","resoudre","resoudre_dans_C","resoudre_systeme_lineaire","restart","restart_modes","restart_vars","resultant","reverse_rsolve","revert","revlist","rhombus","rhs","right","right_triangle","rm_a_z","rm_all_vars","rmbreakpoint","rmmod","rmwatch","romberg","rond","rootof","roots","rotate","rotation","round","row","rowAdd","rowDim","rowNorm","rowSwap","rowdim","rownorm","rowspace","rref","rsolve","saute","sauve","save_history","scalarProduct","scalar_product","scatterplot","sec","segment","select","semi_augment","seq","seqplot","seqsolve","series","shift","shift_phase","show_language","si","sialorssinon","sign","signature","signe","similarity","simp2","simplex_reduce","simplifier","simplify","simult","sin","sin2costan","sincos","single_inter","singular","sinh","sinon","size","sizes","slope","slopeat","slopeatraw","smod","snedecor","snedecor_cdf","snedecor_icdf","solve","solve_zero_extremum","somme","sommet","sort","sphere","spline","split","spread2mathml","spreadsheet","sq","sqrfree","sqrt","square","srand","sst","sst_in","stdDev","stddev","stddevp","sto","string","student","student_cdf","student_icdf","sturm","sturmab","sturmseq","subMat","submatrix","subst","substituer","sum","sum_riemann","suppress","surd","svd","switch_axes","sylvester","symb2poly","syst2mat","tCollect","tExpand","table","tablefunc","tableseq","tabvar","tail","tan","tan2cossin2","tan2sincos","tan2sincos2","tangent","tangente","tanh","tantque","taylor","tchebyshev1","tchebyshev2","tcoeff","tcollect","testfunc","tests","tetrahedron","texpand","textinput","threads_allowed","throw","time","tlin","to","tourne_droite","tourne_gauche","trace","tran","translation","transpose","triangle","triangle_plein","trig2exp","trigcos","trigexpand","trigsin","trigtan","trn","trunc","truncate","tsimplify","type","ufactor","unapply","unarchive","unarchive_ti","unitV","unquote","usimplify","valuation","vandermonde","variance","vector","vers","version","vertices","vertices_abc","vertices_abca","vpotential","watch","whattype","when","while","white","widget_size","with_sqrt","write","writergb","writewav","xcas_mode","xyztrange","yellow","zeros","zip","ztrans"],
  dicho_find:function(tableau,s){
    var l=tableau.length,debut=0,fin=l,milieu;
    if (l==0) return false;
    if (s<tableau[0] || s>tableau[l-1]) return false;
    // s>=tableau[debut] and s<=tableau[fin-1]
    for (;debut<fin-1;){
      milieu=Math.floor((debut+fin)/2);
      // console.log(debut,fin,milieu,tableau[milieu]) 
      if (s>=tableau[milieu]) debut=milieu; else fin=milieu;
    }
    // console.log(s,tableau[debut]);
    if (s==tableau[debut]) return true;
    return false;
  },
  unique_completion:function(tableau,s){
    var l=tableau.length,debut=0,fin=l,milieu;
    if (l==0 || s>tableau[l-1]) return "";
    if (s<tableau[0]) return s==tableau[0].substr(s.length);
    // s>=tableau[debut] and s<=tableau[fin-1]
    for (;debut<fin-1;){
      milieu=Math.floor((debut+fin)/2);
      // console.log(debut,fin,milieu,tableau[milieu]) 
      if (s>=tableau[milieu]) debut=milieu; else fin=milieu;
    }
    // console.log(tableau[debut+1],tableau[debut+1].length);
    // console.log(s,tableau[debut],tableau[debut+1],tableau[debut+2]);
    // s>=tableau[debut]
    if (s==tableau[debut]){
      if (debut+1<l && s==tableau[debut+1].substr(0,s.length) ) return "";
      return s;
    }
    // now s>tableau[debut] and s is supposed to be shorter, hence s!=begin of tableau[debut]
    if (debut+1<l && s!=tableau[debut+1].substr(0,s.length)) return "";
    if (debut+2<l && s==tableau[debut+2].substr(0,s.length)) return "";
    return tableau[debut+1];
  },
  completion:function(cm){
    var s,k;
    if (cm.type=='textarea'){
      k = cm.selectionStart;
      s=cm.value;
    }
    else {
      var pos=cm.getCursor();
      k=pos.ch;
      s=cm.getLine(pos.line);
    }
    var kstart=k;
    // skip at cursor
    for (;k>0;k--){
      var c=s.charCodeAt(k);
      if (UI.is_alphan(c))
	break;
    }
    var kend=k;
    for (;k>=0;k--){
      var c=s.charCodeAt(k);
      if (!UI.is_alphan(c))
	break;
    }
    for (;k<kend;k++){
      var c=s.charCodeAt(k+1);
      if (c>64) break;
    }
    //Module.print(s); Module.print(k); Module.print(kend);
    if (s.length<2){ UI.insert(UI.focused,'?'); return;}
    s=s.substr(k+1,kend-k);
    var sc=UI.unique_completion(UI.xcascmd,s);
    //Module.print(s); Module.print(sc);
    if (cm.type=='textarea'){
      cm.selectionStart=k+1;
      cm.selectionEnd=kstart;
      if (sc!=""){
	UI.insert(cm,sc);
	s=sc;
	cm.selectionStart=k+1;
	cm.selectionEnd=k+1+sc.length;
      }
    } else {
      if (sc!=""){
	cm.setSelection({line:pos.line,ch:k+1},{line:pos.line,ch:pos.ch});
	UI.insert(cm,sc);
	cm.setSelection({line:pos.line,ch:k+1},{line:pos.line,ch:k+1+sc.length});
	s=sc;
      }
      else {
	//console.log(s,k);
	cm.setCursor({line:pos.line,ch:k+1+s.length});
	cm.showHint();
      }
    }
    UI.addhelp('?',s);
  },
  isie:false,    
  scrollatend:function(field){
    if (!UI.isie)
      field.scrollTop=field.scrollHeight;    
  },    
  addhelp: function(prefixe,text){
    document.getElementById('helptxt').value=text;      
    var input=prefixe+text;
    var out=UI.eval(input,input);
    var add=out;
    var helpoutput=document.getElementById('helpoutput');
    helpoutput.innerHTML += add;  
    UI.scrollatend(helpoutput.parentNode); // focus at end
    if (UI.focusaftereval) UI.focused.focus();
  },
  clean:function(text,quote){
    var cmd=text;
    if (quote) cmd=cmd.replace(/\'/g,'\\\'');
    cmd=cmd.replace(/>/g,'&gt;');
    cmd=cmd.replace(/</g,'&lt;');
    if (quote) cmd=cmd.replace(/\"\"/g,'&quote;');    
    return cmd;
  },
  renderhelp: function(text){
    var s=text.substr(1,text.length-2);
    var pos0=s.search("</b>");
    var found=(s.substr(pos0+7,20)!="Best match has score");
    var lh=s.substr(3,pos0-3);
    if (found)
      lh=' (<a href="'+UI.docprefix+eval('longhelp.'+lh)+'" target="_blank">+ de d&eacute;tails</a>)';
    //Module.print(lh);
    var sorig=s;  
    pos1=s.search("<br>");
    if (pos1<0) return sorig;
    var explication=s.substr(0,pos1);
    s=s.substr(pos1+4,s.length-pos1-4);
    pos1=s.search("<br>");
    if (pos1<0) return sorig;
    var syntaxe=s.substr(0,pos1);
    s=s.substr(pos1+4,s.length-pos1-4);
    pos1=s.search("<br>");
    if (pos1<0) return sorig;
    var voiraussi=s.substr(0,pos1);
    var examples=s.substr(pos1+4,s.length-pos1-4);
    if (found)
      s = explication+lh+'<br><tt>'+syntaxe+'</tt><br>Voir aussi: ';
    else
      s = explication.substr(0,pos0);
    while (true){
      pos1=voiraussi.search(',');
      if (pos1 < 0) break;
      var cmd=UI.clean(voiraussi.substr(0,pos1),false);
      if (found)
	s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.addhelp(\'?\',\''+cmd+'\')">'+cmd+'</button>';
      else
	s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="var help=document.getElementById(\'helptxt\');help.value=\''+cmd+'\'; UI.insert(UI.focused!=help?UI.focused:cmentree,\''+UI.clean(cmd,true)+'(\')">'+cmd+'</button>';
      voiraussi = voiraussi.substr(pos1+1,voiraussi.length-pos1-1);
    }
    if (found)
      s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.addhelp(\'?\',\''+voiraussi+'\')">'+voiraussi+'</button>';
    else 
      s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.insert(UI.focused,\''+voiraussi+'(\')">'+voiraussi+'</button>';
    pos1=examples.search(';');
    if (pos1>=0){
      s += '<br>Exemples: ';
      while (true){
	pos1=examples.search(';');
	if (pos1<0) break;
	var cmd=examples.substr(0,pos1);
	cmd=UI.clean(cmd,false);
	s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.insert(UI.focused,\''+UI.clean(cmd,true)+'\')">'+cmd+'</button>';
	examples = examples.substr(pos1+1,examples.length-pos1-1);
      }
    }
    s += '<button class="bouton" onmousedown="event.preventDefault()" onclick="UI.insert(UI.focused,\''+UI.clean(examples,true)+'\')">'+examples+'</button>';
    //console.log(s);
    return s;
  },
  getsel:function(field){
    var startPos = field.selectionStart;
    var endPos = field.selectionEnd;
    var selectedText = field.value.substring(startPos, endPos);
    return selectedText;
  },
  move_caret_or_focus:function(field,n){
    UI.moveCaret(field,n); return;
    if (UI.detectmob()){ UI.moveCaret(field,n); return; }
    while(n>=1){ UI.move_focus(field,1); n--; }
    while(n<=-1){ UI.move_focus(field,-1); n++; }
  },
  set_focused: function(field){ UI.focused=field;},
  selectionne: function(){
    UI.focused.focus();
    if (UI.focused.type!='textarea'){
      if (UI.focused.execCommand)
	UI.focused.execCommand('selectAll');
    }
    else {
      UI.focused.select(); UI.selection=UI.focused.value;
    }
  },
  set_focus:function(s){
    var tmp=document.getElementById(s);
    UI.focused=tmp;
    UI.selectionne(); // if (!UI.is_touch_device()) tmp.focus();
  },
  adjust_focus:function(field){
    var p1=field.parentNode;
    if (p1){
      p1=p1.nextSibling;
      if (p1){
	p1=p1.firstChild;
	if (p1){
	  p1=p1.nextSibling;
	  if (p1 && p1.title=='Editer ce commentaire'){
	    p1.click();
	    return;
	  }
	}
      }
    }
    var p2=field.nextSibling;
    if (p2.CodeMirror){
      p2.CodeMirror.toTextArea();
    }
    field.focus();
  },
  move_focus_end:function(par){
    if (par.firstChild==null) return;
    UI.switch_buttons(par.firstChild,true) 
    par=par.firstChild.firstChild.nextSibling.nextSibling.nextSibling.firstChild;
    if (par.nextSibling.title=="Editer ce commentaire"){
      par.nextSibling.click();
      return;
    }
    if (par.nextSibling==null){
      par=par.parentNode.previousSibling.firstChild;
      UI.adjust_focus(par);
      return;
    } 
    //console.log(par.innerHTML);
    par.style.display='none';
    par=par.nextSibling;
    par.style.display='inherit';
    par.select();
    UI.set_focused(par);
    UI.adjust_focus(par);
    return;
  },
  move_focus_end2:function(par){
    par=par.parentNode.parentNode.parentNode;
    if (!par.nextSibling) par=par.parentNode; // inside a comment 1 more level
    par=par.nextSibling;
    if (par==null || par.firstChild==null) {
      UI.set_focused(cmentree); cmentree.focus();
    }
    else {
      // console.log(par);
      UI.switch_buttons(par.firstChild,true) 
      par=par.firstChild.firstChild.nextSibling.nextSibling.firstChild;
      UI.adjust_focus(par);
    }
  },    
  move_focus:function(field,n){
    // focus on next or previous history level
    if (n>0){
      if (field==cmentree) return;
      if (field.type!="textarea" && field.type!="text")
	field=field.getTextArea();
      if (field.previousSibling==null){
	var par=field.parentNode;
	UI.switch_buttons(par.parentNode,true)
	par=par.nextSibling;
	par=par.firstChild;
	if (par.nextSibling==null){
	  UI.move_focus_end2(par);
	  return;
	}
	par.style.display='none';
	par=par.nextSibling;
	par.style.display='inherit';
	par.select();
	UI.set_focused(par);
	UI.adjust_focus(par);
	return;
      }
      var bidon=field.previousSibling;
      if (bidon.style.display!='none') return;
      bidon.style.display='block';
      field.style.display='none';
      UI.move_focus_end2(field);
      return;
    } // end if n>0
    if (field==cmentree){
      var par=document.getElementById('mathoutput').lastChild;
      if (par==null) return;
      UI.move_focus_end(par);
      return;
    }
    if (field.type!="textarea" && field.type!="text")
      field=field.getTextArea();
    if (field.previousSibling==null){
      var par=field.parentNode.parentNode.parentNode;
      if (!par.previousSibling) par=par.parentNode; // inside a comment 1 more level
      par=par.previousSibling;
      UI.move_focus_end(par);
      return;
    }
    var bidon=field.previousSibling;
    if (bidon.style.display!='none') return;
    bidon.style.display='block';
    field.style.display='none';
    var par=field.parentNode.previousSibling.firstChild;
    UI.adjust_focus(par);
    UI.switch_buttons(par.parentNode.parentNode,true) 
  },
  selline:0,
  selch:0,
  setselbeg:function(field){
    if (field.type!="textarea"&& field.type!="text"){
      var pos=field.getCursor(); // save position
      UI.selline=pos.line; UI.selch=pos.ch;
      //console.log(UI.selline,UI.selch);
      return;
    }
    UI.selch=field.selectionStart;
  },
  setselend:function(field){
    if (field.type!="textarea"&& field.type!="text"){
      var startpos=field.getCursor(); // current position
      field.setSelection({line: UI.selline,ch:UI.selch },startpos);
      field.refresh();
      UI.selection=field.getSelection();
      return;
    }
    var pos1=field.selectionStart;
    var pos2=UI.selch;
    if (pos2>field.value.length) pos2=field.value.length;
    if (pos1>pos2){ var tmp=pos1; pos1=pos2; pos2=tmp; }
    field.setSelectionRange(pos1,pos2);
    UI.selection=field.value.substr(pos1,pos2-pos1);
  },
  indentline:function(field){
    if (field.type!='textarea') field.execCommand('indentAuto');
  },
  moveCaret: function(field, charCount) {
    if (field.type!="textarea" && field.type!="text"){
      var pos=field.getCursor();
      pos.ch = pos.ch+charCount;
      field.setCursor(pos);
      field.refresh();
      // UI.show_curseur();
      return;
    }
    var pos=field.selectionStart;
    pos = pos+charCount;
    if (pos<0) pos=0;
    if (pos>field.value.length) pos=field.value.length;
    field.setSelectionRange(pos,pos);
  },
  show_curseur:function(){
    document.getElementsByClassName("CodeMirror-cursors")[0].style.visibility = "visible";
    var cursors = document.getElementsByClassName("CodeMirror-cursor");
    for (var i = 0; i < cursors.length; i++) {
      cursors[i].style.visibility = "visible";
    }
  },
  moveCaretUpDown: function(field, Count) {
    if (field.type!="textarea"&& field.type!="text"){
      var pos=field.getCursor();
      pos.line = pos.line+Count;
      field.setCursor(pos);
      field.refresh();
      //UI.show_curseur();
      return;
    }
    if (Count<-1){
      var i;
      for (i=0;i>Count;i--)
	UI.moveCaretUpDown(field,-1);
      return;
    }
    if (Count>1){
      var i;
      for (i=0;i<Count;i++)
	UI.moveCaretUpDown(field,1);
      return;
    }
    var pos=field.selectionStart;
    var s=field.value;
    var cur=pos,shift=pos+1,pos1;
    cur--;
    if (cur>=s.length) cur--;
    for (;cur>=0;cur--){
      if (s.charCodeAt(cur)==10){ shift=pos-cur; break; }
    }
    if (Count==-1){
      if (cur<0) return;
      pos1=cur;cur--;
      for (;cur>=0;cur--){
	if (s.charCodeAt(cur)==10) break;
      }
      //console.log(cur,shift);
      pos=cur+shift;
      if (pos>pos1) pos=pos1;
    }
    if (Count==1){
      cur=pos;
      for (;cur<s.length;cur++){
	if (s.charCodeAt(cur)==10) break;
      }
      pos=cur+shift;
      if (pos>=s.length) return;
      pos1=pos;
      for (;pos1>cur;pos1--){
	if (s.charCodeAt(pos1)==10) pos=pos1;
      }
    }
    if (pos<0) pos=0;
    if (pos>field.value.length) pos=field.value.length;
    field.setSelectionRange(pos,pos);
  },
  erase: function(field){
    var par=field.parentNode;
    par=par.parentNode;
    //par.style.display='none';
    par.style.visibility='hidden';
    if (UI.focusaftereval) UI.focused.focus();
    par=par.parentNode;
    var list = par.parentNode;
    if (list.id=='helpoutput')
      list.removeChild(par);
  },
  erase_all_warn:1,
  erase_all: function(field){
    var cur=field.firstChild;
    while (cur){
      //cur.firstChild.style.display='none';
      cur.firstChild.style.visibility='hidden';
      cur=cur.nextSibling;
    }
    if (UI.erase_all_warn==1){
      alert('Pour annuler, cliquer sur Restaurer (Corbeille). Pour confirmer, cliquer sur Vider (Corbeille).');
      UI.erase_all_warn=0;
    }
    if (UI.focusaftereval) cmentree.focus();
  },
  restoretrash:function(){
    var hist=document.getElementById('mathoutput');
    var cur=hist.firstChild;
    while (cur){
      //if (cur.style.display=='none') cur.style.display='block';
      if (cur.firstChild.style.visibility=='hidden') cur.firstChild.style.visibility='visible';
      cur=cur.nextSibling;
    }
  },
  emptytrash:function(){
    var hist=document.getElementById('mathoutput');
    var cur=hist.firstChild;
    while (cur){
      var nxt=cur.nextSibling;
      //if (cur.firstChild.style.display=='none') hist.removeChild(cur);
      if (cur.firstChild.style.visibility=='hidden') hist.removeChild(cur);
      cur=nxt;
    }
    UI.link(0);
  },
  updatelevel: function(field){
    UI.set_editline(field,false);
    UI.set_config_width();
    var pos=field.selectionStart;
    field.innerHTML=field.value;
    if (pos>=0 && pos<field.value.length)
      field.setSelectionRange(pos,pos);
  },
  moveup: function(field){
    var par=field.parentNode;
    par=par.parentNode;
    par=par.parentNode;
    var prev=par.previousSibling;
    var list = par.parentNode;
    list.removeChild(par);
    list.insertBefore(par,prev);
    par.scrollIntoView(false);
    if (UI.focusaftereval) UI.focused.focus();
    UI.link(0);
  },
  movedown: function(field){
    var par=field.parentNode;
    par=par.parentNode;
    par=par.parentNode;
    var nxt=par.nextSibling;
    nxt=nxt.nextSibling;
    var list = par.parentNode;
    list.removeChild(par);
    list.insertBefore(par,nxt);
    par.scrollIntoView(true);
    UI.link(0);
  },
  backspace: function(field){
    //if (UI.focusaftereval) field.focus();
    if (field.type!="textarea"&& field.type!="text"){
      var start=field.getCursor('from');
      var end=field.getCursor('to');
      if (end.line!=start.line || end.ch!=start.ch)
	field.replaceSelection('');
      else {
	var c=start.ch; var l=start.line;
	if (start.ch==0 && start.line==0) return;
	if (c>0){
	  var s=field.getRange({line: l,ch:0},end),i;
	  for (i=0;i<s.length;i++){
	    if (s.charAt(i)!=' ') break;
	  }
	  //console.log(i,s.length,c);
	  if (i==s.length && c>=2){
	    var l1=l-1;
	    for (;l1>=0;--l1){
	      s=field.getLine(l1);
	      for (i=0;i<s.length && i<c;i++){
		if (s[i]!=' ') break;
	      }
	      if (i!=s.length && i<c) break;
	    }
	    if (l1>=0) c=i; else c-=2;
	  }
	  else c--;
	  field.replaceRange('',{line: l,ch:c},end);
	}
	else { l--; var s=field.getRange({line: l,ch:c},end); field.replaceRange('',{line: l,ch:s.length-1},end); }
      }
      var t=field.getTextArea(); t.value=field.getValue();
    } else {
      var pos = field.selectionStart;
      var pos2 = field.selectionEnd;
      var s=field.value;
      if (pos<pos2){
	field.value = s.substring(0, pos)+s.substring(pos2,s.length);
	if (pos<0) pos=0;
	if (pos>field.value.length) pos=field.value.length;
	field.setSelectionRange(pos,pos);
	UI.resizetextarea(field);
	return;
      }
      if (pos>0){
	field.value = s.substring(0, pos-1)+s.substring(pos,s.length);
	pos--;
	if (pos<0) pos=0;
	if (pos>field.value.length) pos=field.value.length;
	field.setSelectionRange(pos,pos);
	UI.resizetextarea(field);
      }
    }
  },
  insert: function(field, value) {
    var myValue=value.replace(/&quote;/g,'\"');
    //console.log('2',field);
    if (UI.focusaftereval) field.focus();
    if (field.type!="textarea" && field.type!="text"){
      if (field.type==undefined && field.firstChild!=undefined){
	// console.log(field.innerHTML);
	UI.insert(field.firstChild,value);
	return;
      }
      var start=field.getCursor('from');
      var end=field.getCursor('to');
      if (end.line!=start.line || end.ch!=start.ch || myValue.length<3)
	field.replaceSelection(myValue);
      else {
	// detect the same command not selected just before
	var parpos=0;
	for (;parpos<myValue.length;++parpos){
	  if (myValue[parpos]=='(') break;
	}
	if (parpos<myValue.length){
	  var S={line:start.line,ch:start.ch};
	  S.ch -= (parpos+1);
	  var deb=S.ch==-1;
	  if (deb) S.ch=0;
	  if (S.ch>=0){
	    var avant=field.getRange(S,end);
	    //console.log('avant avant',avant,S.ch,deb);
	    var tst=avant.length-1;
	    if (!deb && avant[tst]!='('){
	      avant=avant.substr(1,avant.length-1);
	      //console.log('avant avant',avant);
	      --tst;
	    }
	    else {
	      if (avant[tst]=='(')
		++parpos;
	    }
	    //console.log('avant apres',avant);
	    for (;tst>=0;--tst){
	      if (myValue[tst]!=avant[tst]) break;
	    }
	    //console.log('avant',myValue);
	    if (tst<0)
	      myValue=myValue.substr(parpos,myValue.length-parpos);
	    //console.log('apres',myValue);
	  }
	}
	field.replaceSelection(myValue);
      }
      field.execCommand("indentAuto");
      var t=field.getTextArea(); t.value=field.getValue();
    }
    else {
      var pos=field.selectionStart;
      pos=pos+myValue.length;
      //IE support
      if (document.selection) {
	if (UI.focusaftereval) field.focus();
	var sel = document.selection.createRange();
	sel.text = myValue;
      }
      //MOZILLA and others
      else {
	var startPos = field.selectionStart;
	var endPos = field.selectionEnd;
	if (field.selectionStart || field.selectionStart == '0') {
	  field.value = field.value.substring(0, startPos)
	    + myValue
	    + field.value.substring(endPos, field.value.length);
	} else {
	  field.value += myValue;
	}
      }
      field.setSelectionRange(pos,pos);
      UI.resizetextarea(field);
    }
    // UI.show_curseur();
  },
  insertsemi: function(myField, value) {
    if (UI.python_mode)
      return UI.insert(myField,'\n'+value);
    UI.insert(myField,value+';\n');
  },
  resizetextarea:function(field){
    if (field.type!='textarea') return;
    var s=field.value;
    var C=field.cols;
    console.log(C);
    var N=0,i,j=0,n=s.length,c;
    for (i=0;i<n;i++,j++){
      c=s.charCodeAt(i);
      if (c==10 || j==C){
	N++;
	j=0;
      }
    }
    field.rows=N+1;
  },
  changefontsize:function(field,size){
    field.getWrapperElement().style["font-size"] = size+"px";
    field.refresh();
  },
  color_list:['black', 	
  	      'red' 	,
  	      'green' 	,
  	      'yellow' 	,
  	      'blue' 	,
  	      'magenta',
	      'cyan',
  	      'white' 	,
  	      'silver' 	,
  	      'gray' 	,
  	      'maroon' 	,
  	      'purple' 	,
  	      'fuchsia' 	,
  	      'lime' 	,
  	      'olive' 	,
  	      'navy' 	,
  	      'teal' 	,
  	      'aqua' 	,
  	      'antiquewhite' 	,
  	      'aquamarine' 	,
  	      'azure' 	,
  	      'beige' 	,
  	      'bisque' 	,
  	      'blanchedalmond' 	,
  	      'blueviolet' 	,
  	      'brown' 	,
  	      'burlywood' 	,
  	      'cadetblue' 	,
  	      'chartreuse' 	,
  	      'chocolate' 	,
  	      'coral' 	,
  	      'cornflowerblue' 	,
  	      'cornsilk' 	,
  	      'crimson' 	,
  	      'cyan' ,
  	      'darkblue' 	,
  	      'darkcyan' 	,
  	      'darkgoldenrod' 	,
  	      'darkgray' 	,
  	      'darkgreen' 	,
  	      'darkgrey' 	,
  	      'darkkhaki' 	,
  	      'darkmagenta' 	,
  	      'darkolivegreen' 	,
  	      'darkorange' 	,
  	      'darkorchid' 	,
  	      'darkred' 	,
  	      'darksalmon' 	,
  	      'darkseagreen' 	,
  	      'darkslateblue' 	,
  	      'darkslategray' 	,
  	      'darkslategrey' 	,
  	      'darkturquoise' 	,
  	      'darkviolet' 	,
  	      'deeppink' 	,
  	      'deepskyblue' 	,
  	      'dimgray' 	,
  	      'dimgrey' 	,
  	      'dodgerblue' 	,
  	      'firebrick' 	,
  	      'floralwhite' 	,
  	      'forestgreen' 	,
  	      'gainsboro' 	,
  	      'ghostwhite' 	,
  	      'gold' 	,
  	      'goldenrod' 	,
  	      'greenyellow' 	,
  	      'grey' 	,
  	      'honeydew' 	,
  	      'hotpink' 	,
  	      'indianred' 	,
  	      'indigo' 	,
  	      'ivory' 	,
  	      'khaki' 	,
  	      'lavender' 	,
  	      'lavenderblush' 	,
  	      'lawngreen' 	,
  	      'lemonchiffon' 	,
  	      'lightblue' 	,
  	      'lightcoral' 	,
  	      'lightcyan' 	,
  	      'lightgoldenrodyellow' 	,
  	      'lightgray' 	,
  	      'lightgreen' 	,
  	      'lightgrey' 	,
  	      'lightpink' 	,
  	      'lightsalmon' 	,
  	      'lightseagreen' 	,
  	      'lightskyblue' 	,
  	      'lightslategray' 	,
  	      'lightslategrey' 	,
  	      'lightsteelblue' 	,
  	      'lightyellow' 	,
  	      'limegreen' 	,
  	      'linen' 	,
  	      'mediumaquamarine' 	,
  	      'mediumblue' 	,
  	      'mediumorchid' 	,
  	      'mediumpurple' 	,
  	      'mediumseagreen' 	,
  	      'mediumslateblue' 	,
  	      'mediumspringgreen' 	,
  	      'mediumturquoise' 	,
  	      'mediumvioletred' 	,
  	      'midnightblue' 	,
  	      'mintcream' 	,
  	      'mistyrose' 	,
  	      'moccasin' 	,
  	      'navajowhite' 	,
  	      'oldlace' 	,
  	      'olivedrab' 	,
  	      'orangered' 	,
  	      'orchid' 	,
  	      'palegoldenrod' 	,
  	      'palegreen' 	,
  	      'paleturquoise' 	,
  	      'palevioletred' 	,
  	      'papayawhip' 	,
  	      'peachpuff' 	,
  	      'peru' 	,
  	      'pink' 	,
  	      'plum' 	,
  	      'powderblue' 	,
  	      'rosybrown' 	,
  	      'royalblue' 	,
  	      'saddlebrown' 	,
  	      'salmon' 	,
  	      'sandybrown' 	,
  	      'seagreen' 	,
  	      'seashell' 	,
  	      'sienna' 	,
  	      'skyblue' 	,
  	      'slateblue' 	,
  	      'slategray' 	,
  	      'slategrey' 	,
  	      'snow' 	,
  	      'springgreen' 	,
  	      'steelblue' 	,
  	      'tan' 	,
  	      'thistle' 	,
  	      'tomato' 	,
  	      'turquoise' 	,
  	      'violet' 	,
  	      'wheat' 	,
  	      'whitesmoke' 	,
  	      'yellowgreen'],
  arc_en_ciel:function(k){
    var r,g,b;
    k += 21;
    k %= 126;
    if (k<0)
      k += 126;
    if (k<21){
      r=251; g=0; b=12*k;
    }
    if (k>=21 && k<42){
      r=251-(12*(k-21)); g=0; b=251;
    } 
    if (k>=42 && k<63){
      r=0; g=(k-42)*12; b=251;
    } 
    if (k>=63 && k<84){
      r=0; g=251; b=251-(k-63)*12;
    } 
    if (k>=84 && k<105){
      r=(k-84)*12; g=251; b=0;
    } 
    if (k>=105 && k<126){
      r=251; g=251-(k-105)*12; b=0;
    }
    return 'rgb('+r+','+g+','+b+')';
  },
  turtle_color:function(c){
    if (c>=0x100){
      if (c<0x17e)
	return UI.arc_en_ciel(c);
      //console.log('rgb('+Math.floor(c/(256*256))+','+(Math.floor(c/256) % 256)+','+(c%256)+')');
      return 'rgb('+Math.floor(c/(256*256))+','+(Math.floor(c/256) % 256)+','+(c%256)+')';
    }
    return UI.color_list[c];
  },
  pixon_draw:function(id,s){
    var v=eval(s);
    if (!Array.isArray(v)) return;
    //console.log(v[0],v.length);
    var canvas = document.getElementById(id);
    var l=v.length,w=0,h=0;
    if (l<2) return;
    var scale=v[0];
    for (var k=1;k<l;k++){
      var cur=v[k];
      var x=cur[0],y=cur[1];
      //console.log(cur,x,y);
      if (x>w) w=x;
      if (y>h) h=y;
    }
    w=(w+1)*scale;
    h=(h+1)*scale;
    canvas.width=w;
    canvas.height=h;
    //console.log(h,w);
    if (canvas.getContext) {
      var ctx = canvas.getContext('2d');
      for (var k=1;k<l;k++){
	var cur=v[k],cl;
	//console.log(cur);
	if (!Array.isArray(cur) || (cl=cur.length)<2) continue;
	// cur[0]=x, cur[1]=y, cur[2]=color, cur[3]=w if +, h if -
	var x=cur[0]*scale;
	var y=cur[1]*scale;
	ctx.fillStyle=(cl>2)?UI.turtle_color(cur[2]):'black';
	if (cl<4){
	  ctx.fillRect(x,y,scale,scale);
	  continue;
	}
	var h=cur[3]*scale,w=scale;
	if (h<0){ w=-h; h=scale; }
	ctx.fillRect(x,y,w,h);
      }
    }
  },
  turtle_dx:0, // shift frame
  turtle_dy:0,
  turtle_z:1,  // zoom factor
  turtle_maillage:1,
  turtle_draw:function(id,s){
    if (s.length<7) return;
    s=s.substr(5,s.length-6);
    if (s.length>7 && s.substr(s,6)=="pixon("){
      UI.pixon_draw(id,s.substr(6,s.length-7));
      return;
    }
    if (s.length<6 || s.substr(s,5)!="logo(")
      return ;
    s=s.substr(5,s.length-6);
    //console.log(s);
    var v=eval(s);
    if (!Array.isArray(v)) return;
    //console.log(v[0]);
    var canvas = document.getElementById(id);
    var w=canvas.width,h=canvas.height;
    if (canvas.getContext) {
      var ctx = canvas.getContext('2d');
      var turtlezoom=UI.turtle_z,turtlex=UI.turtle_dx,turtley=UI.turtle_dy;
      // maillage
      if (UI.turtle_maillage & 3){
	ctx.fillStyle = 'black';
	var xdecal=Math.floor(turtlex/10.0)*10;
	var ydecal=Math.floor(turtley/10.0)*10;
	if ( (UI.turtle_maillage & 0x3)==1){
	  for (var i=xdecal;i<w+xdecal;i+=10){
	    for (var j=ydecal;j<h+ydecal;j+=10){
	      var X=Math.floor((i-turtlex)*turtlezoom+.5);
	      var Y=Math.floor((j-turtley)*turtlezoom+.5);
	      // console.log(X,Y);
	      ctx.fillRect(X,h-Y,1,1);
	    }
	  }
	}  else {
	  var dj=Math.sqrt(3.0)*10,i0=xdecal;
	  for (var j=ydecal;j<h+ydecal;j+=dj){
	    var J=Math.floor(h-(j-turtley)*turtlezoom);
	    for (var i=i0;i<w+xdecal;i+=10){
	      ctx.fillRect(Math.floor((i-turtlex)*turtlezoom+.5),J,1,1);
	    }
	    i0 += dj;
	    while (i0>=10)
	      i0 -= 10;
	  }
	}
      }
      var l=v.length,i;
      // montre la position et le cap (v[l-1])
      var prec=v[l-1];
      ctx.font = '16px serif';
      ctx.fillStyle = 'yellow';
      ctx.fillRect(w-40, 0, 40, 50);
      ctx.fillStyle = 'black';
      ctx.fillText('x:'+prec[0], w-40, 15);
      ctx.fillText('y:'+prec[1], w-40, 31);
      ctx.fillText('t:'+prec[2], w-40, 49);
      // v[i]=[x(0),y(1),cap(2),status(3),r(4),chaine(5)],
      // couleur=status >> 11
      // longueur_tortue= (status>>3)&0xff
      // direct=status&4 (vrai si angle dans le sens trigo)
      // visible=status&2
      // crayon baisse=status&1
      // si r>0 arc/disque rayon=r & 0x1ff, theta1=(r >> 9) & 0x1ff, theta2=(r >> 18) & 0x1ff
      //        rempli=(r>>27)&0x1
      // si r<0 ligne polygonale extremite v[i] origine v[i+r] (r<0) 
      for (k=1;k<l;k++){
	prec=v[k-1];
	var cur=v[k];
	var preccouleur=prec[3]>>11; // -> FIXME colors
	var curcouleur=prec[3]>>11; // -> FIXME colors
	if (cur[5].length){
	  ctx.font = cur[4]+'px serif';
	  ctx.strokeStyle=ctx.fillStyle = UI.turtle_color(curcouleur);
	  ctx.fillText(cur[5],turtlezoom*(cur[0]-turtlex),h-turtlezoom*(cur[1]-turtley));
	  continue;
	}
	var radius=cur[4],precradius=prec[4];
	if (radius>0){
	  var r=radius&0x1ff,theta1,theta2,rempli,x,y,R,angle;
	  theta1=((precradius+radius)>>9)&0x1ff;
	  theta2=((precradius+radius)>>18)&0x1ff;
	  rempli=(radius >> 27) & 1;
	  R=Math.floor(turtlezoom*r+.5);
	  angle2=Math.PI/180*(theta2-90);
	  angle1=Math.PI/180*(theta1-90);
	  x=Math.floor(turtlezoom*(cur[0]-turtlex-r*Math.cos(angle2))+.5);
	  y=Math.floor(turtlezoom*(cur[1]-turtley-r*Math.sin(angle2))+.5);
	  ctx.beginPath();
	  ctx.arc(x,h-y,R,angle1,angle2,true);
	  ctx.strokeStyle=ctx.fillStyle = UI.turtle_color(curcouleur);
	  if (rempli)
	    ctx.fill();
	  else
	    ctx.stroke();
	  ctx.closePath();
	  continue;
	}
	if (prec[3] & 1){
	  ctx.strokeStyle=ctx.fillStyle = UI.turtle_color(preccouleur);
	  ctx.beginPath();
	  var x1=Math.floor(turtlezoom*(prec[0]-turtlex)+.5),
	      y1=Math.floor(turtlezoom*(prec[1]-turtley)+.5),
	      x2=Math.floor(turtlezoom*(cur[0]-turtlex)+.5),
	      y2=Math.floor(turtlezoom*(cur[1]-turtley)+.5);
	  ctx.moveTo(x1,h-y1);
	  ctx.lineTo(x2,h-y2);
	  ctx.closePath();
	  ctx.stroke();
	}
	if (radius<-1 && k+radius>=0){
	  ctx.strokeStyle=ctx.fillStyle = UI.turtle_color(curcouleur);
	  ctx.beginPath();
	  var x0=Math.floor(turtlezoom*(cur[0]-turtlex)+.5),y0=Math.floor(turtlezoom*(cur[1]-turtley)+.5);
	  //console.log('begin',x0,y0);
	  ctx.moveTo(x0,h-y0);
	  for (var i=-1;i>=radius;i--){
	    prec=v[k+i];
	    var x=Math.floor(turtlezoom*(prec[0]-turtlex)+.5);
	    var y=Math.floor(turtlezoom*(prec[1]-turtley)+.5);
	    //console.log(i,x,y);
	    ctx.lineTo(x,h-y);
	  }
	  //console.log('end',x0,y0);
	  //ctx.lineTo(x0,h-y0);
	  ctx.closePath();
	  ctx.fill(); // automatically close path
	}
      }
      var cur=v[l-1];
      if (cur[3]&2){
	// dessin de la tortue
	var x=Math.floor(turtlezoom*(cur[0]-turtlex)+.5);
	var y=Math.floor(turtlezoom*(cur[1]-turtley)+.5);
	var cost=Math.cos(cur[2]*Math.PI/180);
	var sint=Math.sin(cur[2]*Math.PI/180);
	var turtle_length= (cur[3]>>3)&0xff;
	var Dx=Math.floor(turtlezoom*turtle_length*cost/2+.5);
	var Dy=Math.floor(turtlezoom*turtle_length*sint/2+.5);
	//console.log('tortue',cur,w,h,turtlezoom,x,y,Dx,Dy);
	ctx.strokeStyle=ctx.fillStyle = UI.turtle_color(curcouleur);
	ctx.beginPath();
	ctx.moveTo(x+Dy,h-(y-Dx));
	ctx.lineTo(x-Dy,h-(y+Dx));
	ctx.closePath();
	ctx.stroke();
	if (!(cur[3]&1))
	  ctx.strokeStyle=ctx.fillStyle = UI.turtle_color(curcouleur+1);
	ctx.beginPath();
	ctx.moveTo(x+Dy,h-(y-Dx));
	ctx.lineTo(x+3*Dx,h-(y+3*Dy));
	ctx.closePath();
	ctx.stroke();
	ctx.beginPath();
	ctx.moveTo(x-Dy,h-(y+Dx));
	ctx.lineTo(x+3*Dx,h-(y+3*Dy));
	ctx.closePath();
	ctx.stroke();
      }
    }
  }
}; // closing UI={
