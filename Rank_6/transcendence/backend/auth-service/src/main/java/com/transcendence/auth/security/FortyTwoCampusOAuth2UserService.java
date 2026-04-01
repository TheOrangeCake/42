package com.transcendence.auth.security;

import java.util.List;
import java.util.Map;

import com.transcendence.auth.config.AppSecurityProperties;
import org.springframework.security.oauth2.client.userinfo.DefaultOAuth2UserService;
import org.springframework.security.oauth2.client.userinfo.OAuth2UserRequest;
import org.springframework.security.oauth2.core.OAuth2AuthenticationException;
import org.springframework.security.oauth2.core.OAuth2Error;
import org.springframework.security.oauth2.core.user.OAuth2User;
import org.springframework.stereotype.Service;

@Service
public class FortyTwoCampusOAuth2UserService extends DefaultOAuth2UserService {

  private final AppSecurityProperties props;

  public FortyTwoCampusOAuth2UserService(AppSecurityProperties props) {
    this.props = props;
  }

  @Override
  public OAuth2User loadUser(OAuth2UserRequest userRequest) throws OAuth2AuthenticationException {
    OAuth2User user = super.loadUser(userRequest);

    // Debug (ok en dev, enlève plus tard)
    System.out.println("ATTR KEYS=" + user.getAttributes().keySet());
    System.out.println("CAMPUS RAW=" + user.getAttributes().get("campus"));
    System.out.println("CAMPUS_USERS RAW=" + user.getAttributes().get("campus_users"));
    System.out.println("allowedCampusIds=" + props.getAllowedCampusIds());

    if (props.getAllowedCampusIds() == null || props.getAllowedCampusIds().isEmpty()) {
      throw new OAuth2AuthenticationException(
          new OAuth2Error("campus_config_missing"),
          "No allowed campus configured (app.allowed-campus-ids is empty)"
      );
    }

    boolean allowed = isAllowedCampus(user.getAttributes(), props.getAllowedCampusIds());
    if (!allowed) {
      throw new OAuth2AuthenticationException(
          new OAuth2Error("campus_not_allowed"),
          "You must belong to an allowed 42 campus"
      );
    }

    return user;
  }

  private boolean isAllowedCampus(Map<String, Object> attributes, List<Integer> allowedCampusIds) {
    Object campusUsersObj = attributes.get("campus_users");
    if (campusUsersObj instanceof List<?> list) {
      for (Object o : list) {
        if (o instanceof Map<?, ?> m) {
          Object campusIdObj = m.get("campus_id");
          if (campusIdObj instanceof Number n) {
            int campusId = n.intValue();
            if (allowedCampusIds.contains(campusId)) return true;
          }
        }
      }
    }

    Object campusObj = attributes.get("campus");
    if (campusObj instanceof List<?> list) {
      for (Object o : list) {
        if (o instanceof Map<?, ?> m) {
          Object idObj = m.get("id");
          if (idObj instanceof Number n) {
            int campusId = n.intValue();
            if (allowedCampusIds.contains(campusId)) return true;
          }
        }
      }
    }

    return false;
  }
}
