package com.transcendence.auth.config;

import java.util.ArrayList;
import java.util.List;

import org.springframework.boot.context.properties.ConfigurationProperties;

@ConfigurationProperties(prefix = "app")
public class AppSecurityProperties {

  private List<Integer> allowedCampusIds = new ArrayList<>();

  public List<Integer> getAllowedCampusIds() {
    return allowedCampusIds;
  }

  public void setAllowedCampusIds(List<Integer> allowedCampusIds) {
    this.allowedCampusIds = allowedCampusIds;
  }
}
