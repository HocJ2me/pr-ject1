  const char webPage[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
    <head>
      <title>Đồ án 1 - Danh Huy</title>
      <meta name='viewport' content='width=device-width, initial-scale=1.0' />
      <meta charset='UTF-8'>
      <link href="https://fonts.googleapis.com/css2?family=Roboto:ital@0;1&display=swap" rel="stylesheet">


      <style>
        body {
          background-color: #F7F9FD;
          text-align: center;
          font-family: 'Roboto', sans-serif;
            
        }
        .form-time{
            padding-top: 20px;
            padding-left: 20px;
            display: flex;
            flex-direction: column;
            margin: auto;
            width: 500px;
            background-color: rgb(218, 250, 239);
            border-radius: 10px;
            box-shadow: 2px 2px 2px 1px rgba(0, 0, 0, 0.2);

        }

        .form-time > div{
            margin-bottom: 12px;
            color: #000;
        }
        .form-time__hour,
        .form-time__min,
        .form-time__time,
        .form-time__timer{
            display: flex;
            justify-content: flex-start;
        }

        #gio,
        #phut, 
        #time
        {
            height: 30px;
            min-width: 200px;
            border-color: #ffffff;
            border-radius: 5px;
            font-size: 20px;
            outline: none;
        }
        #henGio, 
        #mayBom1{
            font-weight: bold;
            width: 100px;
            font-size: 20px;
            letter-spacing: 0.1em;
            text-decoration: none;
            color: #fec93b;
            display: inline-block;
            padding: 6px 20px 6px 20px;
            position: relative;
            border: 3px solid #ffffff;
            border-radius: 20px;
            background-color: antiquewhite;
        }

        #henGio:hover,
        #mayBom1:hover{
            cursor: pointer;
            border-color: #fec93b;
        }

        .gio,
        .phut,
        .time,
        .timer{
            min-width: 170px;
            display: flex;
        }
        
        .display-box{
            display: flex;
            flex-direction: column;
            width: 300px;
            margin: auto;
            padding-left: 20px;
            width: 300px;
            font-size: 18px;
            justify-content: center;
            background-color: rgb(155, 253, 220);
            border-radius: 10px;
            box-shadow: 2px 2px 2px 1px rgba(0, 0, 0, 0.2);


        }

        .display-box > div{
            display: flex;
            margin: 10px 0;
        }


        .text-doam,
        .text-maybom{
            font-size: 20px;
            min-width: 120px;
            display: flex;
            align-items: center;
        }

        #doAm1,
        #mayBom1{
            color: #fec93b;
            font-size: 20px;
            
        }

        .logo{
            position: fixed;
            z-index: 999;
            top: 0;
            left: 0;
            width: 50px;
            background-size: cover;
        }

        ::placeholder{
            opacity: 0.4;
        }
        
      </style>
  
    </head>
  
    <script>
    function updateData()
    {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
          if(this.readyState == 4 && this.status == 200)
        {
          var dataESP8266 = xhttp.responseText;
          console.log("dữ liệu esp8266:" + dataESP8266);
          var DataJson = JSON.parse(dataESP8266);
          if(DataJson.doAm1 != null)
          {
            document.getElementById("doAm1").innerHTML = DataJson.doAm1;
          }
          if(DataJson.TTTB1 != null)
          {
           if(DataJson.TTTB1 == "1") mayBom1On();
           else if(DataJson.TTTB1 == "0") mayBom1Off();
          }
        }
      }
      xhttp.open('GET', '/Update', true);
      xhttp.send();
      setTimeout(function(){ updateData() }, 1000);
    } 
  ////
      var i = 0;
      function status_mayBom1() {
        i = i+1;
        if(i%2 == 1){
          mayBom1On();
        }
        else mayBom1Off();
      }
      ////
      function mayBom1On() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("mayBom1").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "mayBom1On", true);
      xhttp.send();
      }
      //
      function mayBom1Off() {
        var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("mayBom1").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "mayBom1Off", true);
      xhttp.send();
      }
      ////
      var j = 0;
      function status_henGio() {
        j = j+1;
        if(j%2 == 1){
          henGioOn();
        }
        else henGioOff();
      }
      ////
      function henGioOn() {
        var data = "{\"gio\":\""+ document.getElementById("gio").value + "\"," +
                "\"phut\":\""+ document.getElementById("phut").value + "\"," +
                "\"timeBom\":\""+ document.getElementById("time").value + "\"}";
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("henGio").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/Input?Input=" + data, true);
      xhttp.send();
      }
      ////
      function henGioOff() {
        var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200)
        {
          document.getElementById("henGio").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "henGioOff", true);
      xhttp.send();
      }
  
    </script>
    <!-- // Bodymain -->
    <body onload = "updateData()">
        <div class="logo">
            <img width="60px" src="https://cdn.haitrieu.com/wp-content/uploads/2021/10/Logo-DH-Bach-Khoa-Ha-Noi-HUST.png" alt="">
        </div>
    <h2>
        <!-- displayBox -->
    <div class="display-box">
        <div>
            <label class="text-doam" for="">ĐỘ ẨM 1:</label> 
            <label id ="doAm1">120 </label> %
        </div>
        <div>
            <label class="text-maybom" for="">MÁY BƠM 1:</label>
            <butto id = "mayBom1" onclick = "status_mayBom1()">OFF</butto>
        </div>
    </div>
     <br>
     <br>
     <div  class="form-time">
         <div  class="form-time__hour">
            <label class="gio" for="gio">Giờ</label>
            <input placeholder="0->23" id="gio" >
         </div>
         <div class="form-time__min">
            <label class="phut" for="phut">Phút</label>
            <input placeholder="0->59" id="phut" >
         </div>
        <div class="form-time__time">
            <label class="time" for="time">Thời gian bơm</label>
            <input id="time" >
        </div>
        <div class="form-time__timer">
            <label class="timer" for="">Hẹn giờ</label>
            <button id = "henGio" onclick="status_henGio()">OFF</button>
        </div>
     </div>
    </h2>
    </body>
  </html>
  )=====";
