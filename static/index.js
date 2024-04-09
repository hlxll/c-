import { useEffect, useState } from "react";
import {Image} from 'antd'
import './index.less'
import errorImg from '@/assets/images/appImage/errorImg.png'
import API from "@/api";

const YunRender=()=>{
    const [allAppData, setAllAppData] = useState([])
    const [DCSServer, setDcsServer] = useState('')//目标DCs
    const [gsServer, setGsServer] = useState('')//跟随
    const [serverOption, setServerOption] = useState([])//仿真
    useEffect(()=>{
        getServerList()
    }, [])
    useEffect(()=>{
        if(DCSServer || gsServer || serverOption){
            init()
        }
    }, [DCSServer, gsServer, serverOption])
    //查询所有服务器列表Id
    const getServerList=()=>{
        API.queryServerList().then(res=>{
            if(res.msg && res.result == '1'){
                let list = JSON.parse(res.msg)
                let arr = []
                list.forEach(item=>{
                    if(item.name == '跟随服务器'){
                        setGsServer(item.id)
                    }else if(item.name == '目标DCS服务器'){
                        setDcsServer(item.id)
                    }else{
                        arr.push(item)
                    }
                })
                setServerOption(arr)
            }
        })
    }
    const init=()=>{
        API.queryServerProcessConfigItem().then(res=>{
            if(res.result == 1){
                let list = JSON.parse(res.msg)
                let followList = []
                let goalList = []
                let simulationList = []
                list.forEach(item=>{
                    if(item.serverId == gsServer){
                        followList.push(item)
                    }else if(item.serverId == DCSServer){
                        goalList.push(item)
                    }else{
                        simulationList.push(item)
                    }
                })
                setAllAppData([
                    {
                        name: '跟随服务器',
                        data: followList
                    },
                    {
                        name: '仿真服务器',
                        data: goalList,
                    },
                    {
                        name: '目标服务器',
                        data: simulationList
                    }
                ])
            }else{
                setAllAppData([])
            }
            
        }).catch(()=>{
            setAllAppData([])
        })
    }
    const openWindow=(item)=>{
        if(item?.processPath){
            if(item?.processPath.indexOf("http://") == 0 || item?.processPath.indexOf("https://") == 0 || item?.processPath.indexOf("ftp://") == 0){
                window.open(item?.processPath, '_blank')
            }else{
                window.open('http://'+item?.processPath, '_blank')
            }
        }
        
    }
    return(
        <div className="yunRender">
            {
                allAppData.map(obj=>{
                    return <div className="yunRenderMain">
                        <div className="yunRenderTitle">{obj.name}</div>
                        <div className="yunRenderContent">
                            {
                                obj.data.map(item=>{
                                    return (
                                        <div className="yunRenderItem"  onClick={()=>{openWindow(item)}}>
                                            <Image className="YRImg" src={require(`@/assets/images/appImage/${item?.imgUrl}.png`)} fallback={errorImg} preview={false}/>
                                            <div className="YRtext" title={item.processName}>{item.processName}</div>
                                        </div>
                                    )
                                })
                            }
                        </div>
                    </div>
                })
            }
        </div>
    )
}
export default YunRender;