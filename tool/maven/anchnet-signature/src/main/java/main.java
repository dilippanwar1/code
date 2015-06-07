// $ mvn clean
// $ mvn package
// $ mvn clean install
import com.google.gson.Gson;
import request.*;

import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: anchnet-002
 * Date: 15-6-4
 * To change this template use File | Settings | File Templates.
 */
public class main {

  // public static  void main(String[] aa){
  //   Http http = new Http();
  //   Gson gson = new Gson();
  //   Map<String,Object> map = Vxnet.describeVxnets();
  //   System.out.println(http.request(gson.toJson(map)));
  // }
  // public static  void main(String[] aa){
  //   Http http = new Http();
  //   Gson gson = new Gson();
  //   Map<String,Object> map = Volume.createVolumes();
  //   System.out.println(http.request(gson.toJson(map)));
  // }
  // public static  void main(String[] aa){
  //   Http http = new Http();
  //   Gson gson = new Gson();
  //   Map<String,Object> map = Instance.terminateInstances();
  //   Map<String,Object> map =Instance.restartInstances();
  //   Map<String,Object> map =Instance.jobs("job-PQ0D37HJ");
  //   System.out.println(http.request(gson.toJson(map)));
  // }
  // public static void main(String[] aa){
  //   Http http = new Http();
  //   Gson gson = new Gson();
  //   Map<String,Object> map = Eip.describeEips();
  //   System.out.println(http.request(gson.toJson(map)));
  // }

  public static void main(String[] aa){
    String params = "{\n" +
      "\t\t\"product\": {\n" +
      "\t\t    \"cloud\": {\n" +
      "\t\t        \"amount\": 1,\n" +
      "\t\t        \"vm\": {\n" +
      "\t\t            \"cpu\": 1,\n" +
      "\t\t            \"mem\": 1024,\n" +
      "\t\t            \"image_id\": \"centos65x64d\",\n" +
      "\t\t            \"name\": \"test\",\n" +
      "\t\t            \"mode\": \"system\",\n" +
      "\t\t            \"login_mode\": \"pwd\",\n" +
      "\t\t            \"password\": \"anchnet20150401\"\n" +
      "\t\t        },\n" +
      "\t\t        \"net0\": true,\n" +
      "\t\t        \"net1\": [],\n" +
      "\t\t        \"hd\": [\n" +
      "\t\t            {\n" +
      "\t\t                \"type\": 0,\n" +
      "\t\t                \"unit\": \"100\",\n" +
      "\t\t                \"name\": \"anchnet应用\"\n" +
      "\t\t            },\n" +
      "\t\t            {\n" +
      "\t\t                \"type\": 0,\n" +
      "\t\t                \"unit\": \"100\",\n" +
      "\t\t                \"name\": \"anchnet数据库\"\n" +
      "\t\t            }\n" +
      "\t\t        ],\n" +
      "\t\t        \"ip\": {\n" +
      "\t\t            \"bw\": \"5\",\n" +
      "\t\t            \"ip_group\": \"eipg-00000000\"\n" +
      "\t\t        }\n" +
      "\t\t    }\n" +
      "\t\t},\n" +
      "\t\t\"zone\": \"ac1\",\n" +
      "\t\t\"token\": \"1HC4XSHVTSRVU5C89NP4\",\n" +
      "\t\t\"action\": \"RunInstances\"\n" +
      "\t\t}";
    String sig = Signature.signature(params, Constant.SECRET_KEY);
    System.out.println(sig);
  }
}
