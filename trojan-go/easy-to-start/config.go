package main

import (
	"github.com/p4gefau1t/trojan-go/log"
	"github.com/p4gefau1t/trojan-go/url"
	"strings"
)

// 去除一些url中读不到的东西,写在go是方便有一天修改

type UrlConfig struct {
	RunType         string   `json:"run_type"`
	RemoteAddr      string   `json:"remote_addr"`
	RemotePort      int      `json:"remote_port"`
	Password        []string `json:"password"`
	url.Websocket   `json:"websocket"`
	url.Shadowsocks `json:"shadowsocks"`
	url.TLS         `json:"ssl"`
}

func NewConfigByShareLink(shareLink string) UrlConfig {
	if shareLink == "" {
		log.Error("url为空")
	}
	info, err := url.NewShareInfoFromURL(shareLink)
	if err != nil {
		log.Error(err)
	}
	wsEnabled := false
	if info.Type == url.ShareInfoTypeWebSocket {
		wsEnabled = true
	}
	ssEnabled := false
	ssPassword := ""
	ssMethod := ""
	if strings.HasPrefix(info.Encryption, "ss;") {
		ssEnabled = true
		ssConfig := strings.Split(info.Encryption[3:], ":")
		if len(ssConfig) != 2 {
			log.Error("invalid shadowsocks config: %s", info.Encryption)
		}
		ssMethod = ssConfig[0]
		ssPassword = ssConfig[1]
	}

	c := UrlConfig{
		RunType:    "client",
		RemoteAddr: info.TrojanHost,
		RemotePort: int(info.Port),
		Password:   []string{info.TrojanPassword},
		TLS: url.TLS{
			SNI: info.SNI,
		},
		Websocket: url.Websocket{
			Enabled: wsEnabled,
			Path:    info.Path,
			Host:    info.Host,
		},
		Shadowsocks: url.Shadowsocks{
			Enabled:  ssEnabled,
			Password: ssPassword,
			Method:   ssMethod,
		},
	}

	return c
}

func GenerateShareLink(this *UrlConfig) {

}
