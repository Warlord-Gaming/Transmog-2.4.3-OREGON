-- BlizzLikeCore integrates as part of this file: CREDITS.md and LICENSE.md
-- ---------------------------------------------------
-- BlizzLike Script to Create MySQL User and Tables --
-- ---------------------------------------------------

GRANT USAGE ON * . * TO 'blizzlike'@'localhost' IDENTIFIED BY 'blizzlike' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 ;

CREATE DATABASE `world` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE DATABASE `characters` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE DATABASE `auth` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;

GRANT ALL PRIVILEGES ON `world` . * TO 'blizzlike'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `characters` . * TO 'blizzlike'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `auth` . * TO 'blizzlike'@'localhost' WITH GRANT OPTION;