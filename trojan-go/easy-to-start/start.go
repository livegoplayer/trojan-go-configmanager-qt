package main

import (
	"C"
	"encoding/json"
	"github.com/p4gefau1t/trojan-go/common"
	"github.com/p4gefau1t/trojan-go/constant"
	_ "github.com/p4gefau1t/trojan-go/easy"
	"github.com/p4gefau1t/trojan-go/log"
	_ "github.com/p4gefau1t/trojan-go/log"
	_ "github.com/p4gefau1t/trojan-go/log/golog"
	_ "github.com/p4gefau1t/trojan-go/log/golog/buffer"
	_ "github.com/p4gefau1t/trojan-go/log/golog/colorful"
	//_ "github.com/p4gefau1t/trojan-go/log/simplelog"
	"github.com/p4gefau1t/trojan-go/proxy"
	_ "github.com/p4gefau1t/trojan-go/proxy/client"
	_ "github.com/p4gefau1t/trojan-go/proxy/custom"
	_ "github.com/p4gefau1t/trojan-go/proxy/forward"
	_ "github.com/p4gefau1t/trojan-go/proxy/nat"
	_ "github.com/p4gefau1t/trojan-go/proxy/server"
	"io/ioutil"
	"strings"

	_ "github.com/p4gefau1t/trojan-go/statistic"
	_ "github.com/p4gefau1t/trojan-go/statistic/memory"
	_ "github.com/p4gefau1t/trojan-go/statistic/mysql"

	_ "github.com/p4gefau1t/trojan-go/tunnel/dokodemo"
	_ "github.com/p4gefau1t/trojan-go/tunnel/freedom"
	_ "github.com/p4gefau1t/trojan-go/tunnel/http"
	_ "github.com/p4gefau1t/trojan-go/tunnel/mux"
	_ "github.com/p4gefau1t/trojan-go/tunnel/router"

	_ "github.com/p4gefau1t/trojan-go/tunnel/shadowsocks"
	_ "github.com/p4gefau1t/trojan-go/tunnel/simplesocks"

	_ "github.com/p4gefau1t/trojan-go/tunnel"
	_ "github.com/p4gefau1t/trojan-go/tunnel/socks"
	_ "github.com/p4gefau1t/trojan-go/tunnel/tls"
	_ "github.com/p4gefau1t/trojan-go/tunnel/tproxy"
	_ "github.com/p4gefau1t/trojan-go/tunnel/transport"
	_ "github.com/p4gefau1t/trojan-go/tunnel/trojan"
	_ "github.com/p4gefau1t/trojan-go/tunnel/websocket"
	_ "github.com/p4gefau1t/trojan-go/url"
	_ "github.com/p4gefau1t/trojan-go/version"
)

var P *proxy.Proxy

// Start 移植了client运行的核心代码，在该项目中找不到可以主动停止的接口,所以抄过来了

//export Start
func Start(path string) {
	data, isJSON, err := detectAndReadConfig(path)
	if err != nil {
		log.Fatal(err)
	}

	if !isJSON {
		log.Fatal(common.NewError("not json file"))
	}

	if data != nil {
		log.Info("trojan-go", constant.Version, "initializing")
		P, err = proxy.NewProxyFromConfigData(data, isJSON)
		if err != nil {
			log.Fatal(err)
		}
		err = P.Run()
		if err != nil {
			log.Fatal(err)
		}
	}
}

//export Stop
func Stop() {
	err := P.Close()
	if err != nil {
		log.Fatal(err)
	}
}

//export ParseShareLinkToJsonFile
func ParseShareLinkToJsonFile(shareLink, outputFilePath string) {

	c := NewConfigByShareLink(shareLink)
	data, err := json.Marshal(&c)

	err = ioutil.WriteFile(outputFilePath, data, 0644)
	if err != nil {
		log.Error(err)
	}
}

////export ParseJsonFileToShareLink
//func ParseJsonFileToShareLink(shareLink, path string) {
//	data, isJSON, err := detectAndReadConfig(path)
//	if err != nil {
//		log.Fatal(err)
//	}
//
//	if !isJSON {
//		log.Fatal(common.NewError("not json file"))
//	}
//
//	cfg := UrlConfig{}
//	err = json.Unmarshal(data, &cfg)
//	if err != nil {
//		log.Fatal(err)
//	}
//}

func main() {
	//shareLink := "trojan://xjy84885390@www.k3s.shop:865#www.k3s.shop%3A865"
	outputFilePath := "F:/projects/qt/build-trojan-go-desktop-Desktop_Qt_6_3_1_MinGW_64_bit-Debug/debug/config/config.json"
	Start(outputFilePath)
}

func detectAndReadConfig(file string) ([]byte, bool, error) {
	isJSON := false
	switch {
	case strings.HasSuffix(file, ".json"):
		isJSON = true
	case strings.HasSuffix(file, ".yaml"), strings.HasSuffix(file, ".yml"):
		isJSON = false
	default:
		log.Fatalf("unsupported config format: %s. use .yaml or .json instead.", file)
	}

	data, err := ioutil.ReadFile(file)
	if err != nil {
		return nil, false, err
	}
	return data, isJSON, nil
}
