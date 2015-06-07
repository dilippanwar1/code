package request;

import com.google.gson.Gson;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created with IntelliJ IDEA.
 * User: anchnet-002
 * Date: 15-3-28
 * To change this template use File | Settings | File Templates.
 */
public class Instance {

  public static Map<String,Object> describeInstances(){
    Map<String,Object> map = new HashMap<String, Object>();
    //        map.put("instances",new String[]{"i-1XSBKXJT","i-A4B96K7P","i-1TATZP4K"});
    //        map.put("search_word", "i-A4B96K7P");
    map.put("status",new String[]{"running","stopped"});
    return Base.putPublic(map,"DescribeInstances");
  }

  public static Map<String,Object>  startInstances(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("instances",new String[]{"i-4OYL66J4"});
    return Base.putPublic(map,"StartInstances");
  }

  public static Map<String,Object> stopInstances(){
    Map<String,Object> map = new HashMap<String, Object>();
    //        i-7DWOUQW5
    //        i-JAHKIXFE
    map.put("instances",new String[]{"i-IWV1X6MM"});
    map.put("force",1);
    return Base.putPublic(map,"StopInstances");
  }

  public static Map<String,Object> restartInstances(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("instances",new String[]{"i-3NPWD3CM"});
    return Base.putPublic(map,"RestartInstances");
  }

  public static Map<String,Object> resetLoginPasswd(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("instances",new String[]{"i-7DWOUQW5","i-JAHKIXFE"});
    map.put("login_passwd","1111ssSS");
    return Base.putPublic(map,"ResetLoginPasswd");
  }

  public static Map<String,Object> terminateInstances(){
    Map<String,Object> map = new HashMap<String,Object>();
    map.put("instances",new String[]{"i-P1PSCJAK"});
    return Base.putPublic(map,"TerminateInstances");
  }

  public static Map<String,Object> describeVxnetInstances(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("status",new String[]{"stopped","running"});
    return Base.putPublic(map,"DescribeVxnetInstances");
  }

  public static Map<String,Object> jobs(String job){
    Map<String,Object> map = new HashMap<String,Object>();
    map.put("job_id",job);
    return Base.putPublic(map,"DescribeJobs");
  }

  public static Map<String,Object> runInstance(){
    Map<String,Object> params=  new HashMap<String, Object>();
    Map<String,Object> product = new HashMap<String, Object>();
    Map<String,Object> cloud = new HashMap<String, Object>();

    cloud.put("amount",1);
    Map<String,Object> vm = new HashMap<String, Object>();
    vm.put("cpu",1);
    vm.put("mem",1024);
    vm.put("image_id","centos65x64d");
    vm.put("name","51idc_api_test");
    vm.put("mode","system");
    vm.put("login_mode","pwd");
    vm.put("password","51idc.coM");
    cloud.put("vm",vm);

    //如要加入公网IP
    //        Map<String,Object> ip = new HashMap<String, Object>();
    //        ip.put("bw",1);
    //        ip.put("ip_group","eipg-98dyd0aj");
    //        cloud.put("ip",ip);
    //        cloud.put("ip","eip-TQYJRFWK");


    //如要公有加入网络
    cloud.put("net0",true);
    //如要同时创建网络
    //        Map<String,Object> net = new HashMap<String, Object>();
    //        net.put("vxnet_name","gao_upprisdn2");
    //        net.put("checked",true);
    //        List<Map<String,Object>> nets = new ArrayList<Map<String, Object>>();
    //        nets.add(net);
    //        cloud.put("net1",nets);
    //如要加入已有网络
    cloud.put("net1",new String[]{"vxnet-EGUADCG4"});


    //如要加入硬盘
    //        List<Map<String,Object>> hds = new ArrayList<Map<String, Object>>();
    //        Map<String,Object> hd1 = new HashMap<String, Object>();
    //        hd1.put("type",0);
    //        hd1.put("unit",10);
    //        hd1.put("name","gao_cloud3hd");
    //        Map<String,Object> hd2 = new HashMap<String, Object>();
    //        hd2.put("type",0);
    //        hd2.put("unit",10);
    //        hd2.put("name","test2");
    //        hds.add(hd1);
    //        hds.add(hd2);
    //        cloud.put("hd",hds);
    //        cloud.put("hd",new String[]{"vol-3P55VY7Z","vol-GZTKW703"});
    product.put("cloud",cloud);
    params.put("product",product);
    return Base.putPublic(params,"RunInstances");
  }

  //    public static Map<String,Object> modifyInstanceAttributes(){
  //        Map<String,Object> map = new HashMap<String, Object>();
  //        map.put("instance","i-A4B96K7P");
  //        map.put("instance_name","rhel lamp—php5.3test");
  //        map.put("description","test");
  //        return Base.putPublic(map,"ModifyInstanceAttributes");
  //    }

  //    public static Map<String,Object> imageList(){
  //        Map<String,Object> map = new HashMap<String,Object>();
  ////        map.put("","")
  //        return Base.putPublic(map,"")
  //    }

  public static String trim(String str){
    String dest = "";
    if (str!=null) {
      Pattern p = Pattern.compile("\\s*|\t|\r|\n");
      Matcher m = p.matcher(str);
      dest = m.replaceAll("");
    }
    return dest;
  }
}
